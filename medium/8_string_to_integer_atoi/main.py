class Solution:
    def myAtoi(self, s: str) -> int:
        out = ""
        seen_any = False
        seen_digit = False
        prev_sign = False
        for c in s:
            if c == " " and not seen_any:
                continue
            try:
                val = int(c)
                if val == 0 and not seen_digit:
                    continue
                out += c
                seen_digit = True
                continue
            except:
                if c in ["+", "-"]:
                    if not seen_digit and not prev_sign:
                        out += c
                        prev_sign = True
                    else:
                        break
                else:
                    break

        if out == "":
            return 0
        else:
            out = int(out)
            if out < -(2**31):
                return -(2**31)
            elif out > 2**31 - 1:
                return 2**31 - 1
            return out


if __name__ == "__main__":
    sol = Solution()
    print(sol.myAtoi("  -42"))
