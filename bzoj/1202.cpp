//BZOJ 1202 badpoet

const
        MAXN = 100;

var
        f, w : array [0..MAXN] of longint;
        flag : boolean;
        i, j, k, n, m, testcase, l, r, tmp, delta : longint;

function find(x : longint) : longint;
var
        rst, tmp : longint;
begin
        if f[x] = x then exit(x);
        tmp := f[x];
        f[x] := find(f[x]);
        w[x] := w[x] + w[tmp];
        exit(f[x]);
end;

begin
        readln(testcase);
        while testcase > 0 do begin
                dec(testcase);
                readln(n, m);
                for i := 0 to n do f[i] := i;
                fillchar(w, sizeof(w), 0);
                flag := true;
                for i := 1 to m do begin
                        readln(l, r, delta);
                        dec(l);
                        if find(l) = find(r) then
                                if w[l] - w[r] = delta then continue
                                else begin
                                        flag := false;
                                end
                        else begin
                                tmp := find(l);
                                f[find(l)] := find(r);
                                w[tmp] := delta + w[r] - w[l];
                        end;
                        if not flag then break;
                end;
                if flag then writeln('true') else writeln('false');
        end;
end.
