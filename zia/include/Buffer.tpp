//
// Created by phill on 14/02/2020.
//

#include "Buffer.hpp"

namespace Zia
{
	MutableBuffer::MutableBuffer() noexcept : m_data(nullptr), m_size(0)
	{};

	MutableBuffer::MutableBuffer(void *data, std::size_t size) noexcept : m_data(data), m_size(size)
	{}

	MutableBuffer::MutableBuffer(Zia::MutableBuffer &&other) noexcept : m_data(other.m_data), m_size(other.m_size)
	{
		other.m_data = nullptr;
		other.m_size = 0;
	}

	MutableBuffer &MutableBuffer::operator=(MutableBuffer &&other) noexcept
	{
		this->m_data = other.m_data;
		this->m_size = other.m_size;
		other.m_data = nullptr;
		other.m_size = 0;
		return *this;
	}

	void *MutableBuffer::Data() const noexcept
	{
		return this->m_data;
	}

	std::size_t MutableBuffer::Size() const noexcept
	{
		return this->m_size;
	}

	MutableBuffer &MutableBuffer::operator+=(std::size_t forward) noexcept
	{
		std::size_t offset = forward < this->m_size ? forward : this->m_size;
		this->m_data = static_cast<char *>(this->m_data) + offset;
		this->m_size -= offset;
		return *this;
	}

	ConstBuffer::ConstBuffer() noexcept : m_data(nullptr), m_size(0)
	{}

	ConstBuffer::ConstBuffer(void const *data, std::size_t size) : m_data(data), m_size(size)
	{}

	ConstBuffer::ConstBuffer(ConstBuffer &&other) noexcept : m_data(other.m_data), m_size(other.m_size)
	{}

	ConstBuffer::ConstBuffer(MutableBuffer &other) noexcept : m_data(other.Data()), m_size(other.Size())
	{}

	ConstBuffer & ConstBuffer::operator=(ConstBuffer &&other) noexcept
	{
		this->m_size = other.m_size;
		this->m_data = other.m_data;
		other.m_data = nullptr;
		other.m_size = 0;
		return *this;
	}

	const void *ConstBuffer::Data() const noexcept
	{
		return this->m_data;
	}

	std::size_t ConstBuffer::Size() const noexcept
	{
		return this->m_size;
	}

	ConstBuffer &ConstBuffer::operator+=(std::size_t forward) noexcept
	{
		std::size_t offset = forward < this->m_size ? forward : this->m_size;
		this->m_data = static_cast<char const *>(this->m_data) + offset;
		this->m_size -= offset;
		return *this;
	}

	inline MutableBuffer operator+(MutableBuffer const &buffer, std::size_t n) noexcept
	{
		auto offset = n > buffer.Size() ? buffer.Size() : n;
		auto new_data = static_cast<char *>(buffer.Data()) + offset;
		auto new_size = buffer.Size() - offset;
		return MutableBuffer(new_data, new_size);
	}

	inline MutableBuffer operator+(std::size_t n, MutableBuffer const &buffer) noexcept
	{
		return buffer + n;
	}

	inline ConstBuffer	operator+(ConstBuffer const &buffer, std::size_t n) noexcept
	{
		auto offset = n > buffer.Size() ? buffer.Size() : n;
		auto new_data = static_cast<char const *>(buffer.Data()) + offset;
		auto new_size = buffer.Size() - offset;
		return ConstBuffer(new_data, new_size);
	}

	inline ConstBuffer operator+(std::size_t n, ConstBuffer const &buffer) noexcept
	{
		return buffer + n;
	}

	//// ***** facilitator ***** /////

	inline ConstBuffer		buffer(ConstBuffer const &buffer) noexcept
	{
		return ConstBuffer(buffer);
	}

	inline ConstBuffer		buffer(ConstBuffer const &buffer, std::size_t max_size) noexcept
	{
		auto offset = max_size < buffer.Size() ? max_size : buffer.Size();
		auto new_data = static_cast<char const *>(buffer.Data()) + offset;
		auto new_size = buffer.Size() - offset;
		return ConstBuffer(new_data, new_size);
	}

	inline ConstBuffer		buffer(void const *data, std::size_t size) noexcept
	{
		return ConstBuffer(data, size);
	}

	template <typename LegacyType, std::size_t N>
	inline ConstBuffer		buffer(LegacyType const (&data)[N]) noexcept
	{
		return ConstBuffer(data, N * sizeof(LegacyType));
	}

	template <typename LegacyType, std::size_t N>
	inline ConstBuffer		buffer(LegacyType const (*data)[N], std::size_t max_size) noexcept
	{
		return ConstBuffer(data, N * sizeof(LegacyType) > max_size ? max_size : N * sizeof(LegacyType));
	}

	template <typename Type, typename Allocator>
	inline ConstBuffer		buffer(std::vector<Type, Allocator> const &container) noexcept
	{
		return ConstBuffer(container.data(), container.size());
	}

	template <typename Type, typename Allocator>
	inline ConstBuffer		buffer(std::vector<Type, Allocator> const &container, std::size_t max_size) noexcept
	{
		return ConstBuffer(container.data(), container.size() > max_size ? max_size : container.size());
	}

	template <typename CharT, typename Traits, typename Allocator>
	inline ConstBuffer		buffer(std::basic_string<CharT, Traits, Allocator> const &container) noexcept
	{
		return ConstBuffer(container.data(), container.size());
	}

	template <typename CharT, typename Traits, typename Allocator>
	inline ConstBuffer		buffer(std::basic_string<CharT, Traits, Allocator> const &container, std::size_t max_size) noexcept
	{
		return ConstBuffer(container.data(), container.size() > max_size ? max_size : container.size());
	}

	inline MutableBuffer		buffer(MutableBuffer const &buffer) noexcept
	{
		return MutableBuffer(buffer);
	}

	inline MutableBuffer		buffer(MutableBuffer const &buffer, std::size_t max_size) noexcept
	{
		auto offset = max_size < buffer.Size() ? max_size : buffer.Size();
		auto new_data = static_cast<char *>(buffer.Data()) + offset;
		auto new_size = buffer.Size() - offset;
		return MutableBuffer(new_data, new_size);
	}

	inline MutableBuffer		buffer(void *data, std::size_t size) noexcept
	{
		return MutableBuffer(data, size);
	}

	template <typename LegacyType, std::size_t N>
	inline MutableBuffer		buffer(LegacyType (&data)[N]) noexcept
	{
		return MutableBuffer(data, N * sizeof(LegacyType));
	}

	template <typename LegacyType, std::size_t N>
	inline MutableBuffer		buffer(LegacyType (&data)[N], std::size_t max_size) noexcept
	{
		return MutableBuffer(data, N * sizeof(LegacyType) > max_size ? max_size : N * sizeof(LegacyType));
	}

	template <typename Type, typename Allocator>
	inline MutableBuffer		buffer(std::vector<Type, Allocator> &container) noexcept
	{
		return MutableBuffer(container.data(), container.size());
	}

	template <typename Type, typename Allocator>
	inline MutableBuffer		buffer(std::vector<Type, Allocator> &container, std::size_t max_size) noexcept
	{
		return MutableBuffer(container.data(), container.size() > max_size ? max_size : container.size());
	}

	template <typename CharT, typename Traits, typename Allocator>
	inline MutableBuffer		buffer(std::basic_string<CharT, Traits, Allocator> &container) noexcept
	{
		return MutableBuffer(container.data(), container.size());
	}

	template <typename CharT, typename Traits, typename Allocator>
	inline MutableBuffer		buffer(std::basic_string<CharT, Traits, Allocator> &container, std::size_t max_size) noexcept
	{
		return MutableBuffer(container.data(), container.size() > max_size ? max_size : container.size());
	}
}