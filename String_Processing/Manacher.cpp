/*
#####################################################
#                                                   #
#               Quality Certificate                 #
#                   I class                         #
#                                                   #
#   Tasks:                                          #
#       - Gorgeous Summation                        #
#           (2024 ICPC Belarus Regional Contest)    #
#                                                   #
#####################################################
*/

void Manacher(vector<int> &text, vector<int> &ans){
    int n = text.size();
    text.insert(text.begin(), 1e5);
    text.push_back(1e7);
    ans.resize(n + 2);
    ans[0] = 1;
    int l = 0, r = 1;
    

    auto triv = [&text](int cent, int start_idx) -> int {
        while(text[start_idx] == text[2 * cent - start_idx]) start_idx++;
        return start_idx;
    };

    int last_idx;
    for(int i = 1; i <= n; i++){
        if(i >= r){
            last_idx = triv(i, i + 1);
        } else {
            last_idx = min(r, ans[l + r - i] + i);
            if(last_idx == r){
                last_idx = triv(i, last_idx);
            }
        }
        ans[i] = last_idx - i;
        if(last_idx > r){
            r = last_idx;
            l = 2 * i - last_idx;
        }
    }
}