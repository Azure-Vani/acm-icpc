while True:
        n = int(raw_input())
        if n == 0:
                break
        if n&1:
                print "Bob"
        else:
                print "Alice"