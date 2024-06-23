from itertools import cycle


def encrypt_message(encoding_type):
    def encrypt_decorator(func):
        def encrypted(*args):
            if encoding_type == 'ROT-13':
                result = ''
                for symbol in func():
                    if symbol.islower():
                        result += chr((ord(symbol) - ord('a') + 13) % 26 + ord('a'))
                    elif symbol.isupper():
                        result += chr((ord(symbol) - ord('A') + 13) % 26 + ord('A'))
                    else:
                        result += symbol
                return result

            elif encoding_type == 'ATBASH':
                result = ''
                first_half = [chr(a) for a in range(97, 110)]
                second_half = [chr(a) for a in range(122, 109, -1)]
                for symbol in func(*args):
                    if 'n' <= symbol.lower() <= 'z':
                        symbol_index = second_half.index(symbol.lower())
                        if symbol.islower():
                            result += first_half[symbol_index]
                        else:
                            result += first_half[symbol_index].upper()
                    elif 'a' <= symbol.lower() <= 'm':
                        symbol_index = first_half.index(symbol.lower())
                        if symbol.islower():
                            result += second_half[symbol_index]
                        else:
                            result += second_half[symbol_index].upper()
                    else:
                        result += symbol

                return result

            elif encoding_type == 'FN-XOR':
                result = ''
                fn = cycle(['6', '2', '5', '2', '9'])
                for symbol in func(*args):
                    result += chr(ord(symbol) ^ ord(next(fn)))
                return result

        return encrypted

    return encrypt_decorator

@encrypt_message('FN-XOR')
def michael_bolton(person, description):
    return f'This is the tale of {person}, {description}!'

print(michael_bolton('Captain Jack Sparrow', 'pirate so brave of the Seven Seas'))