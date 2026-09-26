class Solution {
    unordered_map<string, string> longToShort;
    unordered_map<string, string> shortToLong;
    int counter = 0;
    string base = "http://tinyurl.com/";

public:
    string encode(string longUrl) {
        if (longToShort.count(longUrl)) {
            return longToShort[longUrl];
        }
        string shortUrl = base + to_string(++counter);
        longToShort[longUrl] = shortUrl;
        shortToLong[shortUrl] = longUrl;
        return shortUrl;
    }

    string decode(string shortUrl) {
        return shortToLong[shortUrl];
    }
};