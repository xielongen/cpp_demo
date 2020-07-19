class Normal(object):
    def __init__(self):
        pass


def Fuck(a, b, c, d):
    Normal(
        intension='加锁',
        expect=[
            a < b,
            c > d,
        ],

        inspect=[
            a.T,
            b.size
        ],

        output=[],
        output_expect=[],
        test_case={
            (100, 1000, 'sh000001'): 10000
        }
    )
    a = b + c
    return
