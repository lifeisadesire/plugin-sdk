/*
    Plugin-SDK source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "CVector2D.h"

// constructors

inline CVector::CVector(float value) {
    Set(value);
}

inline CVector::CVector(float x, float y, float z) {
    Set(x, y, z);
}

inline CVector::CVector(const CVector& src) {
    *this = src;
}

#ifdef RW
inline CVector::CVector(const RwV3d& src) {
    FromRwV3d(src);
}
#endif

inline CVector::CVector(const CVector2D& xy, float z) {
    Set(xy.x, xy.y, z);
}

// assignments

inline void CVector::Reset() {
    Set(0.0f);
}

inline void CVector::Set(float value) {
    Set(value, value, value);
}

inline void CVector::Set(float x, float y, float z) {
    this->fX = x;
    this->fY = y;
    this->fZ = z;
}

inline void CVector::operator =(const CVector& src) {
    Set(src.fX, src.fY, src.fZ);
}

#ifdef RW
inline void CVector::FromRwV3d(const RwV3d& src) {
    Set(src.x, src.y, src.z);
}
#endif

inline void CVector::From2D(const CVector2D& xy, float z) {
    Set(xy.x, xy.y, z);
}

inline void CVector::FromSum(const CVector& left, const CVector& right) {
    *this = left;
    *this += right;
}

inline void CVector::FromDiff(const CVector& left, const CVector& right) {
    *this = left;
    *this -= right;
}

inline void CVector::FromLerp(const CVector& begin, const CVector& end, float progress) {
    *this = Lerp(begin, end, progress);
}

inline void CVector::FromCross(const CVector& left, const CVector& right) {
    Set(
        right.fZ * left.fY - left.fZ * right.fY,
        left.fZ * right.fX - left.fX * right.fZ,
        left.fX * right.fY - right.fX * left.fY
    );
}

// FromMultiply in CVector.cpp

// FromMultiply3x3 in CVector.cpp

// conversions

#ifdef RW
inline RwV3d CVector::ToRwV3d() const {
    return RwV3d(fX, fY, fZ);
}
#endif

inline CVector2D CVector::To2D() const {
    return CVector2D(fX, fY);
}

// properties

inline bool CVector::operator ==(const CVector& other) const {
    return fX == other.fX && fY == other.fY && fZ == other.fZ;
}

inline bool CVector::operator !=(const CVector& other) const {
    return fX != other.fX || fY != other.fY || fZ != other.fZ;
}

inline CVector CVector::operator -() const {
    return CVector(-fX, -fY, -fZ);
}

inline float CVector::Distance(const CVector& other) const {
    return Distance(*this, other);
}

inline float CVector::Distance2D(const CVector& other) const {
    return Distance2D(*this, other);
}

inline float CVector::Distance2D(const CVector2D& other) const {
    return Distance2D(*this, other);
}

inline float CVector::Dot(const CVector& other) const {
    return Dot(*this, other);
}

inline CVector CVector::Cross(const CVector& other) const {
    return Cross(*this, other);
}

inline float CVector::Heading() const {
    return atan2(-fX, fY);
}

inline float CVector::Magnitude() const {
    return std::sqrt(MagnitudeSqr());
}

inline float CVector::MagnitudeSqr() const {
    return fX * fX + fY * fY + fZ * fZ;
}

inline float CVector::Magnitude2D() const {
    return std::sqrt(MagnitudeSqr2D());
}

inline float CVector::MagnitudeSqr2D() const {
    return fX * fX + fY * fY;
}

inline bool CVector::IsNormalized() const {
    return fabs(MagnitudeSqr() - 1.0f) < 0.001f;
}

inline bool CVector::IsZero() const {
    return fX == 0.0f && fY == 0.0f && fZ == 0.0f;
}

// modifiers

inline void CVector::operator +=(float value) {
    fX += value;
    fY += value;
    fZ += value;
}

inline void CVector::operator +=(const CVector& other) {
    fX += other.fX;
    fY += other.fY;
    fZ += other.fZ;
}

inline void CVector::operator -=(float value) {
    fX -= value;
    fY -= value;
    fZ -= value;
}

inline void CVector::operator -=(const CVector& other) {
    fX -= other.fX;
    fY -= other.fY;
    fZ -= other.fZ;
}

inline void CVector::operator *=(float multiplier) {
    fX *= multiplier;
    fY *= multiplier;
    fZ *= multiplier;
}

inline void CVector::operator /=(float divisor) {
    fX /= divisor;
    fY /= divisor;
    fZ /= divisor;
}

inline void CVector::Normalise() {
    NormaliseAndMag();
}

inline float CVector::NormaliseAndMag() {
    auto length = Magnitude();
    if (length > 0.0f) *this /= length;
    return length;
}

// static functions

inline CVector CVector::Sum(const CVector& left, const CVector& right) {
    auto result = left;
    result += right;
    return result;
}

inline CVector CVector::Diff(const CVector& left, const CVector& right) {
    auto result = left;
    result -= right;
    return result;
}

inline float CVector::Distance(const CVector& left, const CVector& right) {
    auto result = left;
    result -= right;
    return result.Magnitude();
}

inline float CVector::Distance2D(const CVector& left, const CVector& right) {
    auto result = left.To2D();
    result -= right.To2D();
    return result.Magnitude();
}

inline float CVector::Distance2D(const CVector& left, const CVector2D& right) {
    auto result = left.To2D();
    result -= right;
    return result.Magnitude();
}

inline CVector CVector::Lerp(const CVector& begin, const CVector& end, float progress) {
    return CVector(
        std::lerp(begin.fX, end.fX, progress),
        std::lerp(begin.fY, end.fY, progress),
        std::lerp(begin.fZ, end.fZ, progress)
    );
}

inline float CVector::Dot(const CVector& left, const CVector& right) {
    return left.fZ * right.fZ + left.fY * right.fY + left.fX * right.fX;
}

inline CVector CVector::Cross(const CVector& left, const CVector &right) {
    CVector result;
    result.FromCross(left, right);
    return result;
}

// Multiply in CVector.cpp

// Multiply3x3 in CVector.cpp

// static operators

inline CVector operator +(float value, const CVector& vec) {
    auto result = vec;
    result += value;
    return result;
}

inline CVector operator +(const CVector& vec, float value) {
    auto result = vec;
    result += value;
    return result;
}

inline CVector operator +(const CVector& left, const CVector& right) {
    auto result = left;
    result += right;
    return result;
}

inline CVector operator -(float value, const CVector& vec) {
    auto result = CVector(value);
    result -= vec;
    return result;
}

inline CVector operator -(const CVector& vec, float value) {
    auto result = vec;
    result -= value;
    return result;
}

inline CVector operator -(const CVector& left, const CVector& right) {
    auto result = left;
    result -= right;
    return result;
}

inline CVector operator *(float value, const CVector& vec) {
    auto result = vec;
    result *= value;
    return result;
}

inline CVector operator *(const CVector& vec, float value) {
    auto result = vec;
    result *= value;
    return result;
}

inline CVector operator /(float value, const CVector& vec) {
    auto result = CVector(value);
    result.fX /= vec.fX;
    result.fY /= vec.fY;
    result.fZ /= vec.fZ;
    return result;
}

inline CVector operator /(const CVector& vec, float value) {
    auto result = vec;
    result /= value;
    return result;
}
