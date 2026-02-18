
class Solution:
    # def champagneTower(self, poured: int, query_row: int, query_glass: int) -> float:
        
    #     if poured == 0:
    #         return 0
        
    #     glasses = [poured]

    #     for j in range(query_row):

    #         next_row = [0.0] * (len(glasses) + 1)
    #         for j in range(len(glasses)):
    #             overflow = (glasses[j] - 1.0) / 2.0
    #             if overflow > 0:
    #                 next_row[j] += overflow
    #                 next_row[j + 1] += overflow
            
    #         glasses = next_row
            
    #     return min(glasses[query_glass], 1.0)

    # Space optimisation -> faster because only one array init

    def champagneTower(self, poured: int, query_row: int, query_glass: int) -> float:

        if poured == 0:
            return 0

        glasses = [0.0] * (query_row + 1)
        glasses[0] = poured

        for i in range(1, query_row + 1):
            for j in range(i-1, -1, -1):
                overflow = (glasses[j] - 1.0) / 2.0
                if overflow > 0:
                    glasses[j] = overflow
                    glasses[j + 1] += overflow
                else:
                    glasses[j] = 0
            
        return min(glasses[query_glass], 1.0)
        