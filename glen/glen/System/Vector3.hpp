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
	class Vector3
	{
	public:

		static const Vector3<float>	up;
		static const Vector3<float>	forward;
		static const Vector3<float>	right;

		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/// Creates a Vector3(0, 0).
		///
		////////////////////////////////////////////////////////////
		Vector3();

		////////////////////////////////////////////////////////////
		/// \brief Construct the vector from its coordinates
		///
		/// \param X X coordinate
		/// \param Y Y coordinate
		/// \param Z Z coordinate
		///
		////////////////////////////////////////////////////////////
		Vector3(T X, T Y, T Z);

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
		explicit Vector3(const Vector3<U>& vector);

		explicit Vector3(const glm::vec3& vector);
		operator glm::vec3();
		
		glm::vec3 vec3();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		T x; ///< X coordinate of the vector
		T y; ///< Y coordinate of the vector
		T z; ///< Z coordinate of the vector
	};

	////////////////////////////////////////////////////////////
	/// \relates Vector3
	/// \brief Overload of unary operator -
	///
	/// \param right Vector to negate
	///
	/// \return Memberwise opposite of the vector
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector3<T> operator -(const Vector3<T>& right);

	template <typename T>
	Vector3<T> convert(const glm::vec3 vector);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
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
	Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
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
	Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
	/// \brief Overload of binary operator +
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a vector)
	///
	/// \return Memberwise addition of both vectors
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
	/// \brief Overload of binary operator -
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a vector)
	///
	/// \return Memberwise subtraction of both vectors
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
	/// \brief Overload of binary operator *
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a scalar value)
	///
	/// \return Memberwise multiplication by \a right
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector3<T> operator *(const Vector3<T>& left, T right);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
	/// \brief Overload of binary operator *
	///
	/// \param left  Left operand (a scalar value)
	/// \param right Right operand (a vector)
	///
	/// \return Memberwise multiplication by \a left
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector3<T> operator *(T left, const Vector3<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
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
	Vector3<T>& operator *=(Vector3<T>& left, T right);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
	/// \brief Overload of binary operator /
	///
	/// \param left  Left operand (a vector)
	/// \param right Right operand (a scalar value)
	///
	/// \return Memberwise division by \a right
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	Vector3<T> operator /(const Vector3<T>& left, T right);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
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
	Vector3<T>& operator /=(Vector3<T>& left, T right);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
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
	bool operator ==(const Vector3<T>& left, const Vector3<T>& right);

	////////////////////////////////////////////////////////////
	/// \relates Vector3
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
	bool operator !=(const Vector3<T>& left, const Vector3<T>& right);

	#include <glen/System/Vector3.inl>

	// Define the most common types
	typedef Vector3<int>          Vector3i;
	typedef Vector3<unsigned int> Vector3u;
	typedef Vector3<float>        Vector3f;
	
	// Set a few world global directions
	const Vector3<float>	Vector3<float>::up(0.f, 1.f, 0.f);
	const Vector3<float>	Vector3<float>::forward(0.f, 0.f, 1.f);
	const Vector3<float>	Vector3<float>::right(1.f, 0.f, 0.f);

}

#endif
