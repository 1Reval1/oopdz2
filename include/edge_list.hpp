/// @file edge_list.hpp
#ifndef GRAVIS24_EDGE_LIST_HPP
#define GRAVIS24_EDGE_LIST_HPP

#include <span>
#include <memory> // unique_ptr

namespace gravis24
{

    struct Arc
    {
        int source;
        int target;

        friend auto operator<=>(Arc const&, Arc const&) noexcept = default;
    };


    class EdgeListView
    {
    public:
        virtual ~EdgeListView() = default;

        /// @brief �������� ��� ����.
        [[nodiscard]] virtual auto getEdges() const noexcept
            -> std::span<Arc const> = 0;

        /// @brief ������ ������� ������������� ��������� ��������� �� ����.
        [[nodiscard]] virtual auto getIntAttributeCount() const noexcept
            -> int = 0;

        /// @brief �������� ������ ������������� ��������� ��� ���� ���� (������ ����� ��� � getEdges).
        /// @param attributeIndex < getIntAttributeCount() ��� ���������� ������ span
        [[nodiscard]] virtual auto getIntAttributes(int attributeIndex) const noexcept
            -> std::span<int const> = 0;

        /// @brief ������ ������� ��������� ���� float ��������� �� ����.
        [[nodiscard]] virtual auto getFloatAttributeCount() const noexcept
            -> int = 0;

        /// @brief �������� ������ ��������� float ��� ���� ���� (������ ����� ��� � getEdges).
        /// @param attributeIndex < getFloatAttributeCount() ��� ���������� ������ span
        [[nodiscard]] virtual auto getFloatAttributes(int attributeIndex) const noexcept
            -> std::span<float const> = 0;
    };


    class EditableEdgeList
        : public EdgeListView
    {
    public:
        /// @brief        �������� ����.
        /// @param source �������� �������
        /// @param target ������� �������
        /// @return       ����� ����, ����������� source � target
        virtual auto connect(int source, int target)
            -> int = 0;

        /// @brief        ���������, ���� �� ����, ����������� �������� �������.
        /// @param source �������� �������
        /// @param target ������� �������
        [[nodiscard]] virtual bool areConnected(int source, int target) const noexcept = 0;

        /// @brief        ������� ����, ���� ��� ����.
        /// @param source �������� �������
        /// @param target ������� �������
        /// @return       true, ���� ���� ���� �������, ����� false
        virtual bool disconnect(int source, int target) = 0;

        [[nodiscard]] virtual auto getIntAttributes(int attributeIndex) noexcept
            -> std::span<int> = 0;

        [[nodiscard]] virtual auto getFloatAttributes(int attributeIndex) noexcept
            -> std::span<float> = 0;
    };


    //////////////////////////////////////////////////
    // ������� ��� �������� ��������, �����������
    // EditableEdgeList

    [[nodiscard]] auto newEdgeListUnsortedVector(
            int preallocArcsCount = 0,
            int intAttrsCount     = 0, 
            int floatAttrsCount   = 0
        ) -> std::unique_ptr<EditableEdgeList>;

}

#endif//GRAVIS24_EDGE_LIST_HPP
