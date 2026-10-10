class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while(true) {
            if(tx > ty && tx % ty >= sx)
                tx %= ty;
            else if(ty > tx && ty % tx >= sy)
                ty %= tx;
            else
                break;
        }

        if(tx > ty && tx >= sx && (tx - sx) % ty == 0) tx = sx;
        else if(ty > tx && ty >= sy && (ty - sy) % tx == 0) ty = sy;

        return sx == tx && sy == ty;
    }
};