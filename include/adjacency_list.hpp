/// @file adjacency_list.hpp
#ifndef GRAVIS24_ADJACENCY_LIST_HPP
#define GRAVIS24_ADJACENCY_LIST_HPP

#include <memory>

namespace gravis24
{

    ///////////////////////////////////////////////////////
    // ��������� AdjacencyListView

    class AdjacencyListView
    {
    public:
        virtual ~AdjacencyListView() = default;

        [[nodiscard]] virtual auto getVertexCount() const noexcept
            -> int = 0;

        [[nodiscard]] virtual bool areConnected(int source, int target) const noexcept 
            = 0;

        [[nodiscard]] virtual auto neighborsCount(int vertex) const noexcept
            -> int = 0;

        /// @brief ���� ������� ��� (�������� ������), ���������� ������ span.
        [[nodiscard]] virtual auto getNeighbors(int vertex) const noexcept
            -> std::span<int const> = 0;
    };


    ///////////////////////////////////////////////////////
    // ��������� EditableAdjacencyList

    class EditableAdjacencyList
        : public AdjacencyListView
    {
    public:
        /// @brief  �������� ����� ������� (�������� ���������� ������).
        /// @return ������ ����������� �������
        virtual auto addVertex() -> int = 0;

        /// @brief        �������� target � ����������� source.
        /// @param source �������� ������� ����
        /// @param target ������� ������� ����
        /// @return       true, ���� ���� ���� ���������, false �����
        virtual bool connect(int source, int target) = 0;

        /// @brief        ������� target �� ����������� source.
        /// @param source �������� ������� ����
        /// @param target ������� ������� ����
        /// @return       true, ���� ���� ���� �������, false �����
        virtual bool disconnect(int source, int target) = 0;
    };


    //////////////////////////////////////////////////
    // ������� ��� �������� ��������, �����������
    // EditableAdjacencyList

    [[nodiscard]] auto newAdjacencyListVector(int vertexCount = 0)
        -> std::unique_ptr<EditableAdjacencyList>;

}

#endif//GRAVIS24_ADJACENCY_LIST_HPP
