import unittest
from operator import add, sub, truediv, mul, pow



class _eval:
    valid = " ()0123456789+-/*"
    numbers = "0123456789"
    operants = {
        '**': pow,
        '*': mul, '/': truediv,
        '+': add, '-': sub
    }


    def _tokenize(expression: str):
        expression = expression.strip() + "+"
        tokens = list()
        def _append_number(number_start: int, idx: int):
            if number_start != -1:
                tokens.append(int(expression[number_start:idx]))
                return -1
            return number_start
        number_start = -1
        for idx, c in enumerate(expression):
            if c not in _eval.valid:
                return None
            if c == ' ':
                number_start = _append_number(number_start, idx)
            elif c in _eval.numbers:
                if number_start == -1:
                    number_start = idx
            else:
                number_start = _append_number(number_start, idx)
                if c == '*' and len(tokens) > 0 and tokens[-1] == '*':
                    tokens[-1] = '**'
                else:
                    tokens.append(c)
        tokens.pop()
        return tokens


    def _build_tree(tokens: list, idx: int, local = True):
        data = list()
        is_operator = False
        while idx < len(tokens) and tokens[idx] != ')':
            if is_operator:
                if tokens[idx] not in _eval.operants:
                    return None, None
                data.append(tokens[idx])
                is_operator = False
            else:
                if tokens[idx] == '(':
                    part, idx = _eval._build_tree(tokens, idx + 1)
                    if part == None:
                        return None, None
                    data.append(part)
                elif isinstance(tokens[idx], int):
                    data.append(tokens[idx])
                else:
                    return None, None
                is_operator = True
            idx += 1
        if len(data) % 2 == 0: 
            return None, None
        if local and idx >= len(tokens):
            return None, None
        return data, idx


    def _prec_eval(tree: list, *operators):
        operator = None
        result = list()
        is_operator = False
        for value in tree:
            if is_operator:
                if value not in operators:
                    result.append(value)
                operator = value
                is_operator = False
            else:
                if operator not in operators:
                    result.append(value)
                else:
                    result[-1] = operator(result[-1], value)
                is_operator = True
        return result


    def _evaluate(tree: list | int):
        if not isinstance(tree, list):
            return tree
        for idx, value in enumerate(tree):
            if isinstance(value, list):
                tree[idx] = _eval._evaluate(value)
            elif value in _eval.operants:
                tree[idx] = _eval.operants[value]
        tree = _eval._prec_eval(tree, pow)
        tree = _eval._prec_eval(tree, mul, truediv)
        tree = _eval._prec_eval(tree, add, sub)
        return tree[0]



def eval(expression: str):
    tokens = _eval._tokenize(expression)
    if tokens is None:
        return None
    tree, _ = _eval._build_tree(tokens, 0, False)
    try:
        return _eval._evaluate(tree)
    except ZeroDivisionError:
        return None
    

    
class TestEval(unittest.TestCase):

    def test_valid_expressions(self):
        test_cases = [
            ("((3 * 10) - 4) + (78 / (2 - 1))", 104.0),
            ("13 + (42 - 12) * 3", 103.0),
            ("2 ** 3 * 4", 32.0),
            ("10 / 2 + 8", 13.0),
            ("0 / 5", 0.0),
            ("2 * 0 + 8", 8.0),
            ("(4 - 8) / 6", -2/3),
            ("(((5 + 2) * 3) - 10 ) / 2", 5.5),
            ("3 * (5-2)", 9.0),
            ("   98/   7 ", 14.0)
        ]
        for expression, expected_result in test_cases:
            result = eval(expression)
            self.assertEqual(result, expected_result)


    def test_invalid_expressions(self):
        test_cases = [
            "13 + (42 - 12 * 3",
            "-5 * 10 + 2",
            "8/ (3 - 3)) ",
            "5 * (6 + 3",
            "5 + * 10",
            "abc / 2",
            "5 % 3",
            "4 & 8",
            "",
        ]
        for expression in test_cases:
            result = eval(expression)
            self.assertIsNone(result)



if __name__ == '__main__':
    unittest.main()
