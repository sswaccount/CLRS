/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-04-12 17:04:50
 * @LastEditors: ssw
 * @LastEditTime: 2022-04-13 15:57:26
 */
#include <iostream>
#include <vector>
using namespace std;
int expand(string &s, int l, int r)
{
    while (l >= 0 && r < s.size() && s[l] == s[r])
    {
        l--;
        r++;
    }
    return r - l - 2 >> 1;
}
string Manacher(string s)
{
    if (s.empty() || s.size() < 2)
        return s;
    string new_s = "#";
    for (char c : s)
    {
        new_s += c;
        new_s += "#";
    }
    int n = new_s.size();
    int right = -1;
    int center = -1;
    int start = 0;
    int end = -1;
    vector<int> arm_len;
    for (int i = 0; i < n; ++i)
    {
        int cur_arm_len;
        if (right >= i)
        {
            int minLen = min(right - i, arm_len[2 * center - i]);
            cur_arm_len = expand(new_s, i - minLen, i + minLen);
        }
        else
        {
            cur_arm_len = expand(new_s, i, i);
        }
        arm_len.push_back(cur_arm_len);
        if (i + cur_arm_len > right)
        {
            center = i;
            right = i + cur_arm_len;
        }
        if (cur_arm_len * 2 + 1 > end - start)
        {
            start = i - cur_arm_len;
            end = i + cur_arm_len;
        }
    }
    string answer;
    for (int i = start; i <= end; ++i)
        if (new_s[i] != '#')
            answer += new_s[i];
    return answer;
}
int main()
{
    string s = "babad";
    cout << Manacher(s) << endl;
    return 0;
}