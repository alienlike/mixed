#include <iostream.h>
#include "mixed.h"

int main() {
    Mixed m1,m2;
    cout << "\n\nGimme a mixed number (m1): ";
    cin >> m1;
    cout << "\nMixed " << m1;
    cout << "\nDouble " << m1.Evaluate();
    m1.Simplify();
    cout << "\nSimplified " << m1;
    m1.ToFraction();
    cout << "\nFraction " << m1;
    cout << "\n\nGimme another mixed number (m2): ";
    cin >> m2;
    if(m1<m2)
        cout << "\nm1 < m2";
    if(m1>m2)
        cout << "\nm1 > m2";
    if(m1<=m2)
        cout << "\nm1 <= m2";
    if(m1>=m2)
        cout << "\nm1 >= m2";
    if(m1==m2)
        cout << "\nm1 == m2";
    if(m1!=m2)
        cout << "\nm1 != m2";
    cout << "\nThe sum is " << (m1 + m2);
    cout << "\nThe difference is " << (m1 - m2);
    cout << "\nThe product is " << (m1 * m2);
    cout << "\nThe quotient is " << (m1 / m2);
    m1.Simplify();
    m2.Simplify();
    cout << "\n\nm1 is " << m1 << " and m2 is " << m2;
    cout << "\n\n";
    return 0;
}
