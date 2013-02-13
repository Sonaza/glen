#ifndef GLEN_VECTOR3_HPP
#define GLEN_VECTOR3_HPP

#include <glm/glm.hpp>

namespace glen
{
	////////////////////////////////////////////////////////////
	/// \brief Utility template class for manipulating
	///        2-dimensional vectors
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	class Vector4
	{
	public:

		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/// Creates a Vector4(0, 0).
		///
		////////////////////////////////////////////////////////////
		Vector4();

		////////////////////////////////////////////////////////////
		/// \brief Construct the vector from its coordinates
		///
		/// \param X X coordinate
		/// \param Y Y coordinate
		/// \param Z Z coordinate
		/// \param W W coordinate
		///
		////////////////////////////////////////////////////////////
		Vector4(T X, T Y, T Z, T W);

		////////////////////////////////////////////////////////////
		/// \brief Construct the vector from another type of vector
		///
		/// This constructor doesn't replace the copy constructor,
		/// it's called only when U != T.
		/// A call to this constructor will fail to compile if U
		/// is not convertible to T.
		///
		/// \param vector Vector to convert
		///
		////////////////////////////////////////////////////////////
		template <typename U>
		explicit Vector4(const Vector4<U>& vector);

		explicit Vector4(const glm::vec4& vector);
		operator glm::vec4();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		T x; ///< X coordinate of the vector
		T y; ///< Y coordinate of the vector
		T z; ///< Z coordinate of the vector
		T w; ///< W coordinate of the vector
	};

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of unary operator -
	///
	/// \param right Vector to negate
	///
	/// \return Memberwise opposite of the vector
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector4<T> operator -(const Vector4<T>& right);

	template <typename T>
	Vector4<T> convert(const glm::vec4 vector);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator +=
	///
	/// This operator performs a memberwise addition of both vectors,
	/// and assigns the result to \a left.
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a vector)
	///
	/// \return Reference to \a left
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector4<T>& operator +=(Vector4<T>& left, const Vector4<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator -=
	///
	/// This operator performs a memberwise subtraction of both vectors,
	/// and assigns the result to \a left.
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a vector)
	///
	/// \return Reference to \a left
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector4<T>& operator -=(Vector4<T>& left, const Vector4<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator +
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a vector)
	///
	/// \return Memberwise addition of both vectors
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector4<T> operator +(const Vector4<T>& left, const Vector4<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator -
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a vector)
	///
	/// \return Memberwise subtraction of both vectors
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector4<T> operator -(const Vector4<T>& left, const Vector4<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator *
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a scalar value)
	///
	/// \return Memberwise multiplication by \a right
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector4<T> operator *(const Vector4<T>& left, T right);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator *
	///
	/// \param left  Left operand (a scalar value)
	/// \param right Right operand (a vector)
	///
	/// \return Memberwise multiplication by \a left
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector4<T> operator *(T left, const Vector4<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator *=
	///
	/// This operator performs a memberwise multiplication by \a right,
	/// and assigns the result to \a left.
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a scalar value)
	///
	/// \return Reference to \a left
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector4<T>& operator *=(Vector4<T>& left, T right);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator /
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a scalar value)
	///
	/// \return Memberwise division by \a right
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector4<T> operator /(const Vector4<T>& left, T right);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator /=
	///
	/// This operator performs a memberwise division by \a right,
	/// and assigns the result to \a left.
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a scalar value)
	///
	/// \return Reference to \a left
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector4<T>& operator /=(Vector4<T>& left, T right);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator ==
	///
	/// This operator compares strict equality between two vectors.
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a vector)
	///
	/// \return True if \a left is equal to \a right
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	bool operator ==(const Vector4<T>& left, const Vector4<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector4
	/// \brief Overload of binary operator !=
	///
	/// This operator compares strict difference between two vectors.
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a vector)
	///
	/// \return True if \a left is not equal to \a right
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	bool operator !=(const Vector4<T>& left, const Vector4<T>& right);

	#include <glen/System/Vector4.inl>

	// Define the most common types
	typedef Vector4<int>          Vector4i;
	typedef Vector4<unsigned int> Vector4u;
	typedef Vector4<float>        Vector4f;

}

#endif
