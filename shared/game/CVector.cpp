/*
    Plugin-SDK source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "CVector.h"

#ifdef HAS_CMATRIX
#include <CMatrix.h>

// assignments

void CVector::FromMultiply(CMatrix const& matrix, CVector const& point) {
    FromMultiply3x3(matrix, point);
    *this += matrix.pos;
}

void CVector::FromMultiply3x3(const CMatrix& matrix, const CVector& vector) {
    Set(
        matrix.right.fX * vector.fX + matrix.up.fX * vector.fY + matrix.at.fX * vector.fZ,
        matrix.right.fY * vector.fX + matrix.up.fY * vector.fY + matrix.at.fY * vector.fZ,
        matrix.right.fZ * vector.fX + matrix.up.fZ * vector.fY + matrix.at.fZ * vector.fZ
    );
}

// static functions

CVector CVector::Multiply(const CMatrix& matrix, const CVector& point) {
    CVector result;
    result.FromMultiply(matrix, point);
    return result;
}

CVector CVector::Multiply3x3(const CMatrix& matrix, const CVector& vector) {
    CVector result;
    result.FromMultiply3x3(matrix, vector);
    return result;
}
#endif
