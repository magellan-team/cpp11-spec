#ifndef H27311E03_142A_4CE7_B43B_D2717148A560
#define H27311E03_142A_4CE7_B43B_D2717148A560

#include <vector>

class C1 {};

struct C2
{
    virtual void func1() = 0;
    virtual void func2(int) const = 0;
    virtual void func3() volatile = 0;
    virtual void func4() const volatile = 0;

    virtual ~C2();
};

struct C3 : C2
{
    int a;
    std::vector<int> b;

private:
    void func1() override {}
    virtual void func2(int) const override {}
    virtual void func3() volatile override {}
    virtual void func4() const volatile override {}
};

enum E1 { E1_ENUM };
enum class E2 {};
enum class E3 : int {};
enum struct E4 {};

union U1 { int i; long l; };
union U2 { C1 c1; C3 c3; };

#endif
