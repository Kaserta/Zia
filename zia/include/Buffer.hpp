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

		/**
		 * Construit un buffer vide
		 */

		MutableBuffer() noexcept;

		/**
		 * Construit un buffer avec la segmentation donnée
		 * @param data Un pointeur
		 * @param size Taille de la donnée
		 */

		MutableBuffer(void *data, std::size_t size) noexcept;
		MutableBuffer(MutableBuffer const &other) noexcept = default;
		MutableBuffer(MutableBuffer &&other) noexcept;
		MutableBuffer	&operator=(MutableBuffer const &other) noexcept = default;
		MutableBuffer	&operator=(MutableBuffer &&other) noexcept;

		/**
		 * Récupère la segmentation mémoire
		 * @return Un pointeur
		 */

		void 		*Data() const noexcept;

		/**
		 *  Récupère la taille de la segmentation mémoire
		 * @return Une taille
		 */

		std::size_t	Size() const noexcept;

		/**
		 * Déplace le début du buffer par rapport à un nombre d'octects
		 * @param forward Le nombre d'octects
		 * @return Le buffer
		 */

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

		/**
		 * Construit un buffer vide
		 */

		ConstBuffer() noexcept;

		/**
		 * Construit un buffer avec la segmentation donnée
		 * @param data Un pointeur
		 * @param size Taille de la donnée
		 */

		ConstBuffer(void const *data, std::size_t size);
		ConstBuffer(ConstBuffer const &other) noexcept = default;
		ConstBuffer(ConstBuffer &&other) noexcept;

		/**
		 *  Construit un buffer à partir d'un buffer modifiable
		 */

		explicit ConstBuffer(MutableBuffer &) noexcept;
		ConstBuffer	&operator=(ConstBuffer const &) noexcept = default;
		ConstBuffer	&operator=(ConstBuffer &&) noexcept;

		/**
		 * Récupère la segmentation mémoire
		 * @return Un pointeur
		 */

		const void 	*Data() const noexcept;

		/**
		 *  Récupère la taille de la segmentation mémoire
		 * @return Une taille
		 */

		std::size_t	Size() const noexcept;

		/**
		 * Déplace le début du buffer par rapport à un nombre d'octects
		 * @param forward Le nombre d'octects
		 * @return Le buffer
		 */

		ConstBuffer	&operator+=(std::size_t forward) noexcept;

	private:
		const void	*m_data;
		std::size_t	m_size;
	};

	/**
	 * Créer un nouveau buffer modifiable dont le début est décalé depuis le debut de l'entrée
	 * @param buffer Le buffer
	 * @param n Le décalage
	 * @return Un buffer modifiable
	 */

	inline MutableBuffer operator+(MutableBuffer const &, std::size_t n) noexcept;
	inline MutableBuffer operator+(std::size_t n, MutableBuffer const &) noexcept;

	/**
	 * Créer un nouveau buffer non-modifiable dont le début est décalé depuis le debut de l'entrée
	 * @param buffer Le buffer
	 * @param n Le décalage
	 * @return Un buffer non-modifiable
	 */

	inline ConstBuffer	operator+(ConstBuffer const &buffer, std::size_t n) noexcept;
	inline ConstBuffer operator+(std::size_t n, ConstBuffer const &) noexcept;

	/**
	 * Creér un buffer non-modifiable à partir d'un autre
	 * @param buffer un buffer
	 * @return Une copie de buffer non-modifiable
	 */

	inline ConstBuffer		buffer(ConstBuffer const &buffer) noexcept;

	/**
	 * Creér un buffer non-modifiable à partir d'un autre
	 * @param buffer un buffer
	 * @param max_size La taille maximum des données à copier
	 * @return Une copie de buffer non-modifiable
	 */

	inline ConstBuffer		buffer(ConstBuffer const &buffer, std::size_t max_size) noexcept;

	/**
	 * Créer un buffer non-modifiable à partir d'un pointeur
	 * @param data Le pointeur
	 * @param size La taille de la segmentation mémoire
	 * @return Un buffer non-modifiable
	 */

	inline ConstBuffer		buffer(void const *data, std::size_t size) noexcept;

	/**
	 * Créer un buffer non-modifiable à partir de la déclaration classique d'un tableau
	 * @tparam LegacyType Un type quelconque
	 * @tparam N La taille du tableau (automatique)
	 * @param data Le tableau
	 * @return Un buffer non-modifiable
	 */

	template <typename LegacyType, std::size_t N>
	inline ConstBuffer		buffer(LegacyType const (&data)[N]) noexcept;

	/**
	 * Créer un buffer non-modifiable à partir de la déclaration classique d'un tableau
	 * @tparam LegacyType Un type quelconque
	 * @tparam N La taille du tableau (automatique)
	 * @param data Le tableau
	 * @param max_size La taille maximum des données à copier
	 * @return Un buffer non-modifiable
	 */

	template <typename LegacyType, std::size_t N>
	inline ConstBuffer		buffer(LegacyType const (&data)[N], std::size_t max_size) noexcept;

	/**
	 * Créer un buffer non-modifiable à partir d'un vecteur
	 * @tparam Type Le type contenus de vecteur
	 * @tparam Allocator L'allocateur du vecteur
	 * @param container Le vecteur
	 * @return Un buffer non-modifiable
	 */

	template <typename Type, typename Allocator>
	inline ConstBuffer		buffer(std::vector<Type, Allocator> const &container) noexcept;

	/**
	 * Créer un buffer à partir d'un vecteur
	 * @tparam Type Le type contenus de vecteur
	 * @tparam Allocator L'allocateur du vecteur
	 * @param container Le vecteur
	 * @param max_size limite la taille maximum des données respectif de la taille de Type
	 * @return Un buffer non-modifiable
	 */

	template <typename Type, typename Allocator>
	inline ConstBuffer		buffer(std::vector<Type, Allocator> const &container, std::size_t max_size) noexcept;

	/**
	 * Créer un buffer non-modifiable à partir d'une string
	 * @param container La string
	 * @return Un buffer non-modifiable
	 */

	template <typename CharT, typename Traits, typename Allocator>
	inline ConstBuffer		buffer(std::basic_string<CharT, Traits, Allocator> const &container) noexcept;

	/**
	 * Créer un buffer non-modifiable à partir d'une string
	 * @param container La string
	 * @param max_size La taille maximum à copier
	 * @return Un buffer non-modifiable
	 */

	template <typename CharT, typename Traits, typename Allocator>
	inline ConstBuffer		buffer(std::basic_string<CharT, Traits, Allocator> const &container, std::size_t max_size) noexcept;

	/**
	 * Creér un buffer à partir d'un autre
	 * @param buffer un buffer
	 * @return Une copie de buffer modifiable
	 */

	inline MutableBuffer		buffer(MutableBuffer const &) noexcept;

	/**
	 * Creér un buffer modifiable à partir d'un autre
	 * @param buffer un buffer
	 * @param max_size La taille maximum des données à copier
	 * @return Une copie de buffer modifiable
	 */

	inline MutableBuffer		buffer(MutableBuffer const &, std::size_t max_size) noexcept;

	/**
	 * Créer un buffer modifiable à partir d'un pointeur
	 * @param data Le pointeur
	 * @param size La taille de la segmentation mémoire
	 * @return Un buffer modifiable
	 */

	inline MutableBuffer		buffer(void *data, std::size_t) noexcept;

	/**
	 * Créer un buffer modifiable à partir de la déclaration classique d'un tableau
	 * @tparam LegacyType Un type quelconque
	 * @tparam N La taille du tableau (automatique)
	 * @param data Le tableau
	 * @return Un buffer modifiable
	 */

	template <typename LegacyType, std::size_t N>
	inline MutableBuffer		buffer(LegacyType (&)[N]) noexcept;

	/**
	 * Créer un buffer modifiable à partir de la déclaration classique d'un tableau
	 * @tparam LegacyType Un type quelconque
	 * @tparam N La taille du tableau (automatique)
	 * @param data Le tableau
	 * @param max_size La taille maximum des données à copier
	 * @return Un buffer modifiable
	 */

	template <typename LegacyType, std::size_t N>
	inline MutableBuffer		buffer(LegacyType (&)[N], std::size_t max_size) noexcept;

	/**
	 * Créer un buffer modifiable à partir d'un vecteur
	 * @tparam Type Le type contenus de vecteur
	 * @tparam Allocator L'allocateur du vecteur
	 * @param container Le vecteur
	 * @return Un buffer modifiable
	 */

	template <typename Type, typename Allocator>
	inline MutableBuffer		buffer(std::vector<Type, Allocator> &) noexcept;

	/**
	 * Créer un buffer modifiable à partir d'un vecteur
	 * @tparam Type Le type contenus de vecteur
	 * @tparam Allocator L'allocateur du vecteur
	 * @param container Le vecteur
	 * @param max_size limite la taille maximum des données respectif de la taille de Type
	 * @return Un buffer modifiable
	 */

	template <typename Type, typename Allocator>
	inline MutableBuffer		buffer(std::vector<Type, Allocator> &, std::size_t max_size) noexcept;

	/**
	 * Créer un buffer modifiable à partir d'une string
	 * @param container La string
	 * @return Un buffer modifiable
	 */

	template <typename CharT, typename Traits, typename Allocator>
	inline MutableBuffer		buffer(std::basic_string<CharT, Traits, Allocator> &) noexcept;

	/**
	 * Créer un buffer modifiable à partir d'une string
	 * @param container La string
	 * @param max_size La taille maximum à copier
	 * @return Un buffer modifiable
	 */

	template <typename CharT, typename Traits, typename Allocator>
	inline MutableBuffer		buffer(std::basic_string<CharT, Traits, Allocator> &, std::size_t max_size) noexcept;
}

#include "Buffer.tpp"

#endif //ZIA_BUFFER_HPP
