// Name: Nathaniel Wingfield
// Section: 3
// File: mixed.h
// Asg:  #7
// Date: 11/24/02
//
// Purpose:  Definition of the mixed number class 'Mixed'

#include <iostream.h>
#include "mixed.h"

Mixed::Mixed() {
    sign = 1;
    whole = 0;
    numerator = 0;
    denominator = 1;
}

Mixed::Mixed(int w) {
    if(w < 0) {
        sign = -1;
        whole = w * -1;
    }
    else {
        sign = 1;
        whole = w;
    }
    numerator = 0;
    denominator = 1;
}

Mixed::Mixed(int w, int n, int d) {
    
    bool signSet = false; // flag
    bool validInput = true; // flag
    int sn;

    if (w) { // if the whole part is not 0
        if (w < 0) {
            w *= -1; // set whole to a positive number
            sn = -1; // set the sign to negative
            signSet = true; // set the flag
        }
        else {
            sn = 1; // set the sign to positive
            signSet = true; // set the flag
        }
    }

    if (n) { // if the numerator is not 0
        if (n < 0) {
            if (!signSet) {
                n *= -1; // set numerator to positive
                sn = -1; // set the sign to negative
                signSet = true; // set the flag
            }
            else
                validInput = false; // set the input to invalid
        }
        else if (n > 0 && !signSet) {
            sn = 1;
            signSet = true;
        }
    }

    if (d <= 0)
        validInput = false; // set the input to invalid
    else if (!signSet) {
        sn = 1; // if the sign hasn't been set by now, set it to positive
        signSet = true; // set the flag
    }

    if(validInput) {
        sign = sn;
        whole = w;
        numerator = n;
        denominator = d;
    }
    else {
        sign = 1;
        whole = 0;
        numerator = 0;
        denominator = 1;
    }
    
}

double Mixed::Evaluate() {
    double result = sign * (whole + double(numerator) / denominator);
    return result;
}

void Mixed::ToFraction() {
    numerator += whole * denominator;
    whole = 0;
}

void Mixed::Simplify() {
    // fix improper fraction
    if(numerator >= denominator) {
        int quotient = numerator / denominator;
        whole += quotient;
        numerator -= quotient * denominator;
    }
    // convert to lowest terms
    bool finished = false;
    while(!finished) {
        bool found = false;
        for(int i = 2; i < denominator; i++) { // start our loop at 2 or we'll be going forever!
            if ( !(numerator % i) && !(denominator % i) ) { // if both n. and d. are divisible by this number
                numerator /= i; // divide n. by the number
                denominator /= i; // and divide d. by the number
                found = true;
            }
        }
        if (!found)
            finished = true;
    }
}

ostream& operator << (ostream& s, const Mixed& m)
{
    bool signSet = false;
    if(m == Mixed(0))
        s << 0; // print a zero
    else {
        // whole part
        if(m.whole) {            
            s << (m.whole * m.sign);
            signSet = true;
        }
        if(m.numerator) {
            if(m.whole)
                s << ' ';
            // numerator
            if(!signSet) {
                s << (m.numerator * m.sign);
                signSet = true;
            }
            else
                s << m.numerator;
            // denominator
            s << '/' << m.denominator;
        }
    }    
    return s;
}

istream& operator >> (istream& s, Mixed& m) {
    
    bool signSet = false; // flag
    bool validInput = true; // flag
    int sn, w, n, d;

    s >> w; // read the whole part
    if (w) { // if the whole part is not 0
        if (w < 0) {
            w *= -1; // set whole to a positive number
            sn = -1; // set the sign to negative
            signSet = true; // set the flag
        }
        else {
            sn = 1; // set the sign to positive
            signSet = true; // set the flag
        }
    }
    
    s >> n; // read the numerator
    if (n) { // if the numerator is not 0
        if (n < 0) {
            if (!signSet) {
                n *= -1; // set numerator to positive
                sn = -1; // set the sign to negative
                signSet = true; // set the flag
            }
            else
                validInput = false; // set the input to invalid
        }
        else if (n > 0 && !signSet) {
            sn = 1;
            signSet = true;
        }
    }

    s.get(); // consume the slash
    s >> d; // read the denominator
    if (d <= 0)
        validInput = false; // set the input to invalid
    else if (!signSet) {
        sn = 1; // if the sign hasn't been set by now, set it to positive
        signSet = true; // set the flag
    }

    if(validInput) {
        m.sign = sn;
        m.whole = w;
        m.numerator = n;
        m.denominator = d;
    }
    else {
        m.sign = 1;
        m.whole = 0;
        m.numerator = 0;
        m.denominator = 1;
    }
    
    return s;
}

bool operator < (Mixed m1, Mixed m2) {
    // get rid of the whole number part
    m1.ToFraction();
    m2.ToFraction();
    // calculate each numerator assuming a common denominator, not forgetting the sign
    int n1 = m1.sign * m1.numerator * m2.denominator;
    int n2 = m2.sign * m2.numerator * m1.denominator;
    // then compare!
    if(n1 < n2)
        return true;
    else
        return false;
}

bool operator > (Mixed m1, Mixed m2) {
    return m2 < m1;
}

bool operator == (Mixed m1, Mixed m2) {
    return ( !(m1<m2) && !(m1>m2) );
}

bool operator != (Mixed m1, Mixed m2) {
    return !(m1==m2);
}

bool operator <= (Mixed m1, Mixed m2) {
    return (m1<m2 || m1==m2);
}

bool operator >= (Mixed m1, Mixed m2) {
    return m2 <= m1;
}

Mixed operator + (Mixed m1, Mixed m2) {
    int n, d, n1, n2;
    m1.ToFraction();
    m2.ToFraction();
    // calculate each numerator assuming a common denominator, not forgetting the sign
    n1 = m1.sign * m1.numerator * m2.denominator;
    n2 = m2.sign * m2.numerator * m1.denominator;
    // take the sum of the numerators
    n = n1 + n2;
    // use the common denominator
    d = m1.denominator * m2.denominator;
    // create the new mixed number 
    Mixed a(0,n,d);
    a.Simplify();
    return a;
}

Mixed operator - (Mixed m1, Mixed m2) {
    int n, d, n1, n2;
    m1.ToFraction();
    m2.ToFraction();
    // calculate each numerator assuming a common denominator, not forgetting the sign
    n1 = m1.sign * m1.numerator * m2.denominator;
    n2 = m2.sign * m2.numerator * m1.denominator;
    // take the difference of the numerators
    n = n1 - n2;
    // use the common denominator
    d = m1.denominator * m2.denominator;
    // create the new mixed number
    Mixed a(0,n,d);
    a.Simplify();
    return a;
}

Mixed operator * (Mixed m1, Mixed m2) {
    int n, d;
    m1.ToFraction();
    m2.ToFraction();
    n = m1.sign * m1.numerator * m2.sign * m2.numerator;
    d = m1.denominator * m2.denominator;
    Mixed a(0,n,d);
    a.Simplify();
    return a;
}

Mixed operator / (Mixed m1, Mixed m2) {
    int n, d;
    m1.ToFraction();
    m2.ToFraction();
    n = m1.sign * m1.numerator * m2.sign * m2.denominator;
    d = m1.denominator * m2.numerator;
    Mixed a(0,n,d);
    a.Simplify();
    return a;
}
