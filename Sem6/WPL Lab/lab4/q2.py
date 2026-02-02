import sys 

num = int(sys.argv[1])
a = [1,2,3,4,5,6,7,8,9]

def search(l, r, e):
    m=(l+r)//2
    if l==r:
        return 1
    if a[m]==e:
        return 0
    if a[m]<e:
        return search(m+1, r, e)
    if a[m]>e:
        return search(l, r-1, e)

print(("Found", "Not Found")[search(0,8,num)])
