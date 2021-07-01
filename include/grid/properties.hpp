class Properties
{
    int score = 0;
    int moves = 30;

    bool isLocked = false;

public:
    int getMoves();
    int getScore();

    void addMoves(int delta);
    void subtractMoves(int delta);

    void addScore(int delta);
    void subtractScore(int delta);

    void lockProperties();
    void unlockProperties();

    bool stillHaveMoves();
};