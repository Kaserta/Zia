/**
 * @file Buffer.hpp
 * Ce fichier contient tous les éléments pour faire les buffers
 */

#ifndef ZIA_BUFFER_HPP
#define ZIA_BUFFER_HPP

#include <vector>
#include <string>
#include <type_traits>

namespace Zia
{
	class MutableBuffer
	{
	public:
		using type = MutableBuffer;
		using const_type = const type &;

	public:
		MutableBuffer() noexcept;
		MutableBuffer(void *data, std::size_t size) noexcept;
		MutableBuffer(MutableBuffer const &other) noexcept = default;
		MutableBuffer(MutableBuffer &&other) noexcept;
		MutableBuffer	&operator=(MutableBuffer const &other) noexcept = default;
		MutableBuffer	&operator=(MutableBuffer &&other) noexcept;

		void 		*Data() const noexcept;
		std::size_t	Size() const noexcept;

		MutableBuffer	&operator+=(std::size_t forward) noexcept;

	private:
		void		*m_data;
		std::size_t	m_size;
	};

	class ConstBuffer
	{
	public:
		using type = ConstBuffer;
		using const_type = const type &;

	public:
		ConstBuffer() noexcept;
		ConstBuffer(void const *data, std::size_t size);
		ConstBuffer(ConstBuffer const &other) noexcept = default;
		ConstBuffer(ConstBuffer &&other) noexcept;
		explicit ConstBuffer(MutableBuffer &) noexcept;
		ConstBuffer	&operator=(ConstBuffer const &) noexcept = default;
		ConstBuffer	&operator=(ConstBuffer &&) noexcept;

		const void 	*Data() const noexcept;
		std::size_t	Size() const noexcept;

		ConstBuffer	&operator+=(std::size_t forward) noexcept;

	private:
		const void	*m_data;
		std::size_t	m_size;
	};

	inline MutableBuffer operator+(MutableBuffer const &, std::size_t n) noexcept;
	inline MutableBuffer operator+(std::size_t n, MutableBuffer const &) noexcept;

	inline ConstBuffer	operator+(ConstBuffer const &, std::size_t n) noexcept;
	inline ConstBuffer operator+(std::size_t n, ConstBuffer const &) noexcept;


	/////

	inline ConstBuffer		buffer(ConstBuffer const &buffer) noexcept;
	inline ConstBuffer		buffer(ConstBuffer const &buffer, std::size_t max_size) noexcept;

	inline ConstBuffer		buffer(void const *data, std::size_t size) noexcept;

	template <typename LegacyType, std::size_t N>
	inline ConstBuffer		buffer(LegacyType const (&)[N]) noexcept;

	template <typename LegacyType, std::size_t N>
	inline ConstBuffer		buffer(LegacyType const (&)[N], std::size_t max_size) noexcept;

	template <typename Type, typename Allocator>
	inline ConstBuffer		buffer(std::vector<Type, Allocator> const &) noexcept;

	template <typename Type, typename Allocator>
	inline ConstBuffer		buffer(std::vector<Type, Allocator> const &, std::size_t max_size) noexcept;

	template <typename CharT, typename Traits, typename Allocator>
	inline ConstBuffer		buffer(std::basic_string<CharT, Traits, Allocator> const &) noexcept;

	template <typename CharT, typename Traits, typename Allocator>
	inline ConstBuffer		buffer(std::basic_string<CharT, Traits, Allocator> const &, std::size_t max_size) noexcept;

	/**
	 * Create another buffer of the same type
	 * @return A MutableBuffer
	 */

	inline MutableBuffer		buffer(MutableBuffer const &) noexcept;
	inline MutableBuffer		buffer(MutableBuffer const &, std::size_t max_size) noexcept;

	inline MutableBuffer		buffer(void *, std::size_t) noexcept;

	template <typename LegacyType, std::size_t N>
	inline MutableBuffer		buffer(LegacyType (&)[N]) noexcept;

	template <typename LegacyType, std::size_t N>
	inline MutableBuffer		buffer(LegacyType (&)[N], std::size_t max_size) noexcept;

	template <typename Type, typename Allocator>
	inline MutableBuffer		buffer(std::vector<Type, Allocator> &) noexcept;

	template <typename Type, typename Allocator>
	inline MutableBuffer		buffer(std::vector<Type, Allocator> &, std::size_t max_size) noexcept;

	template <typename CharT, typename Traits, typename Allocator>
	inline MutableBuffer		buffer(std::basic_string<CharT, Traits, Allocator> &) noexcept;

	template <typename CharT, typename Traits, typename Allocator>
	inline MutableBuffer		buffer(std::basic_string<CharT, Traits, Allocator> &, std::size_t max_size) noexcept;
}

#include "Buffer.tpp"

#endif //ZIA_BUFFER_HPP
