class Properties
{
    int score = 0;
    int moves = 30;
    int multiplier = 1;

    bool isLocked = false;

public:
    int getMoves();
    int getScore();
    int getMultiplier();

    void addMoves(int delta);
    void subtractMoves(int delta);

    void addScore(int delta);
    void subtractScore(int delta);

    void addMultiplier(int delta);

    void lockProperties();
    void unlockProperties();

    bool stillHaveMoves();
};