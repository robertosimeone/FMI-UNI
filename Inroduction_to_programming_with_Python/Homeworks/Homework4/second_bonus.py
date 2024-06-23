def isequal(first_word, second_word):
    if len(first_word) != len(second_word):
        return False
    for letter in first_word:
        if first_word.count(letter) != second_word.count(letter):
            return False
    return True


class Dyslexic:
    def __init__(self, obj):
        self.obj = obj

    def __enter__(self):
        return Dyslexic(self.obj)

    def __exit__(self, exc_type, exc_val, exc_tb):
        pass

    def __getattr__(self, item):
        attributes = [attribute for attribute in dir(self.obj) if attribute[:2] != '__' and attribute[:-3:-1] != '__']
        for attribute in attributes:
            if isequal(attribute,item):
                return getattr(self.obj, attribute)
        raise Exception(f"{self.obj.__class__.__name__} object has no dyslexic attributes {item}")

class Baba:
    abc = 5
    def __init__(self):
        self.c = 10
    def retcurr(self):
        return self

baba = Baba()
with Dyslexic(baba) as dysl_b:
    print(dysl_b.bob)




