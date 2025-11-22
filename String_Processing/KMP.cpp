/*
#####################################################
#                                                   #
#               Quality Certificate                 #
#                   NULL class                      #
#                                                   #
#   Tasks:                                          #
#                                                   #
#####################################################
*/

void KMP(vector<int> &text, vector<int> &pi){
    int n = text.size();
    assert(pi.size() >= n);
    int pidx;
    pi[0] = 0;
    for(int i = 1; i < n; i++){
        pidx = pi[i - 1];
        while(pidx > 0 && text[i] != text[pidx]) pidx = pi[pidx - 1];
        if(text[i] == text[pidx]) pidx++;
        pi[i] = pidx;
    }
}