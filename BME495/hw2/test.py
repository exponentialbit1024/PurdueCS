from logic_gates import AND
from logic_gates import NOT
from logic_gates import OR
from logic_gates import XOR

if __name__ == '__main__':

    print("AND")
    And = AND()
    print("1, 1", And(True, True))
    print("1, 0", And(True, False))
    print("0, 1", And(False, True))
    print("0, 0", And(False, False))
    print("")

    print("NOT")
    Not = NOT()
    print("1, 1", Not(True))
    print("0, 0", Not(False))
    print("")

    print("OR")
    Or = OR()
    print("1, 1", Or(True, True))
    print("1, 0", Or(True, False))
    print("0, 1", Or(False, True))
    print("0, 0", Or(False, False))
    print("")

    print("XOR")
    Xor = XOR()
    print("1, 1", Xor(True, True))
    print("1, 0", Xor(True, False))
    print("0, 1", Xor(False, True))
    print("0, 0", Xor(False, False))
    print("")
