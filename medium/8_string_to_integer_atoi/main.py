class Solution:
    def myAtoi(self, s: str) -> int:
        out = ""
        seen_any = False
        seen_digit = False
        prev_sign = False
        stop = False
        for c in s:
            if c == " ":
                if not seen_any:
                    continue
                else:
                    break
            try:
                val = int(c)
                out += c
                seen_digit = True
                seen_any = True
                continue
            except:
                if c in ["+", "-"]:
                    if not seen_digit and not prev_sign:
                        if c == "-":
                            out += c
                        prev_sign = True
                    else:
                        stop = True
                else:
                    stop = True

            seen_any = True

            if stop:
                break

        if out == "":
            return 0
        else:
            try:
                out = int(out)
            except:
                return 0
            if out < -(2**31):
                return -(2**31)
            elif out > 2**31 - 1:
                return 2**31 - 1
            return out
