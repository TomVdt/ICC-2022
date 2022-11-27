

def extract(l: list):
    
    n = len(l)
    a = l[0]
    new_l = [a]
    m = 1
    for i in range(1, n):
        if m < 2:
            new_l.append(l[i])
            m += 1
        if a != l[i]:
            m = 1
        a = l[i]
    return new_l


print(extract([4,4,4,6,6,4,4,4,4,4,5]))
