#ifndef ACCOUNT
#define ACCOUNT

struct AccountAttr {
        int CurrentBalance;
        int MinBalance;
        int MaxBalance;
        bool FrozenAccount;
};

struct Bank {
	int numAccount;
	Account acc[];
};

// Bank * p;
// p->numA;
// p->acc[4];

#endif

