from itertools import combinations
from typing import List


def time2str(hours, minutes):
    hVal = sum([2**i for i in hours])
    mVal = sum([2**j for j in minutes])
    if hVal > 11:
        return None
    if mVal > 59:
        return None
    hstr = str(hVal)
    mstr = str(mVal)
    if len(mstr) == 1:
        mstr = "0" + mstr

    return hstr + ":" + mstr


class Solution:

    def readBinaryWatch(self, turnedOn: int) -> List[str]:

        if turnedOn >= 9:
            return []

        # We have 2 rows with possible values as:
        values = {"hours": [2**i for i in range(4)], "mins": [2**i for i in range(5)]}

        n_bits_hours = 4
        n_bits_mins = 6
        max_num_hours = 3
        max_num_mins = 5
        nH = min(turnedOn, max_num_hours)
        nM = min(turnedOn, max_num_mins)

        strTime = []

        for h in range(nH + 1):
            m = turnedOn - h
            if m > nM:
                print("skip")
                continue
            bitsH = list(combinations(range(n_bits_hours), h))
            bitsM = list(combinations(range(n_bits_mins), turnedOn - h))

            for bH in bitsH:
                for bM in bitsM:
                    vT = time2str(bH, bM)
                    if vT:
                        strTime.append(vT)

        return strTime
