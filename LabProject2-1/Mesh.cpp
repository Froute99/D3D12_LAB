
#include "stdafx.h"
#include "Mesh.h"
#include "GraphicsPipeline.h"


void Draw2DLine(HDC hDCFrameBuffer, _3DLab::Point3D& previousProject,
	_3DLab::Point3D& currentProject) {
	// ���� ��ǥ���� 2���� ȭ�� ��ǥ��� ��ȯ�ϰ�
	// ��ȯ�� �� ��(�ȼ�)�� �������� �׸�
	_3DLab::Point3D previous =
		_3DLab::GraphicsPipeline::ScreenTransform(previousProject);

	_3DLab::Point3D current =
		_3DLab::GraphicsPipeline::ScreenTransform(currentProject);
	::MoveToEx(hDCFrameBuffer, static_cast<long>(previous.x),
		static_cast<long>(previous.y), nullptr);
	::LineTo(hDCFrameBuffer, static_cast<long>(current.x),
		static_cast<long>(current.y));
}

namespace _3DLab {
	Polygon::Polygon(int numberOfVertices) {
		this->m_numberOfVertices = numberOfVertices;
		m_ptrToVertices = new Vertex[this->m_numberOfVertices];
	}

	Polygon::~Polygon() {
		if (m_ptrToVertices)
			delete[] m_ptrToVertices;
	}

	// i think parameter vertex should be const reference
	void Polygon::SetVertex(int indexNumber, Vertex vertex) {
		if (m_ptrToVertices && (indexNumber >= 0) && (indexNumber < m_numberOfVertices)) {
			m_ptrToVertices[indexNumber] = vertex;
		}
	}

	Mesh::Mesh(int numberOfPolygons) {
		m_numberOfPolygons = numberOfPolygons;
		m_ptrToPolygons = new Polygon * [numberOfPolygons];
	}

	Mesh::~Mesh() {
		if (m_ptrToPolygons) {
			for (int i = 0; i < m_numberOfPolygons; ++i) {
				if (m_ptrToPolygons[i]) {
					delete m_ptrToPolygons[i];
				}
				delete[] m_ptrToPolygons;
			}
		}
	}

	void Mesh::SetPolygon(int indexNumber, Polygon* ptrToPolygon) {
	// �޽��� �ٰ��� ����
		if ((0 <= indexNumber) && (indexNumber < m_numberOfPolygons)) {
			m_ptrToPolygons[indexNumber] = ptrToPolygon;
		}
	}

	/*
	 * ù��° for�� j�� i�� ����� ������ m_ptrToPolygons�� ���� ��������
	 * ù��° vertex�� ���� ó���� �ִ� ������ polygons �߿� ���� �ִٸ�
	 * numberOfVertices �� 1�� �ǹǷ� for���� �����ϰ� ��
	 * initialProject�� �������� �ʾƼ�
	 * ���� �߻����� ũ���ð� �Ͼ�� ����
	 */
	void Mesh::Render(HDC hDCFrameBuffer) {
		Point3D initialProject, previousProject, intersect;
		bool previousInside = false, initialInside = false,
			currentInside = false, intersectInside = false;

		// �޽��� �����ϴ� ��� polygons ������
		for (int j = 0; j < m_numberOfPolygons; ++j) {
			int numberOfVertices = m_ptrToPolygons[j]->m_numberOfVertices;
			Vertex* vertices = m_ptrToPolygons[j]->m_ptrToVertices;

			// �ٰ����� ù��° vertex�� ���� ���� ��ȯ�Ѵ�
			previousProject = initialProject =
				GraphicsPipeline::Project(vertices[0].m_position);

			// ��ȯ�� ���� ���� �簢���� ���ԵǴ��� ���
			previousInside = initialInside =
				(-1.f <= initialProject.x) && (initialProject.x <= 1.f)
				&& (-1.f <= initialProject.y) && (initialProject.y <= 1.f);

			// �ٰ����� �����ϴ� ��� �������� ���� ���� ��ȯ�ϰ� �������� ������
			for (int i = 1; i < numberOfVertices; ++i) {
				Point3D currentProject =
					GraphicsPipeline::Project(vertices[i].m_position);
				// ���� ������ ���� ���� �簢���� ���ԵǴ��� ���
				currentInside =
					(-1.f <= currentProject.x) && (currentProject.x <= 1.f)
					&& (-1.f <= currentProject.y) && (currentProject.y <= 1.f);
				// ���� ������ ���� ���� �簢���� ���ԵǸ� ���� ���� ���� ���� �������� �׸�
				if (((previousProject.z >= 0.f) || (currentProject.z >= 0.f))
					&& (currentInside || previousInside)) {
					::Draw2DLine(hDCFrameBuffer, previousProject, currentProject);
					previousProject = currentProject;
					previousInside = currentInside;
				}

				// �ٰ����� ������ vertex�� ù��° vertex�� �������� �׸�
				if (((previousProject.z >= 0.f) || (initialProject.z >= 0.f))
					&& (initialInside || previousInside)) {
					::Draw2DLine(hDCFrameBuffer, previousProject, initialProject);
				}
			}
		}
	}

	CubeMesh::CubeMesh(float width, float height, float depth)
		: Mesh(6) {
		float halfWidth = width * 0.5f;
		float halfHeight = height * 0.5f;
		float halfDepth = depth * 0.5f;

		Polygon* pFrontFace = new Polygon(4);
		pFrontFace->SetVertex(0, Vertex(-halfWidth, +halfHeight, +halfDepth));
		pFrontFace->SetVertex(1, Vertex(+halfWidth, +halfHeight, -halfDepth));
		pFrontFace->SetVertex(2, Vertex(+halfWidth, -halfHeight, -halfDepth));
		pFrontFace->SetVertex(3, Vertex(-halfWidth, -halfHeight, -halfDepth));
		SetPolygon(0, pFrontFace);
		Polygon* pTopFace = new Polygon(4);
		pTopFace->SetVertex(0, Vertex(-halfWidth, +halfHeight, +halfDepth));
		pTopFace->SetVertex(1, Vertex(+halfWidth, +halfHeight, +halfDepth));
		pTopFace->SetVertex(2, Vertex(+halfWidth, +halfHeight, -halfDepth));
		pTopFace->SetVertex(3, Vertex(-halfWidth, +halfHeight, -halfDepth));
		SetPolygon(1, pTopFace);
		Polygon* pBackFace = new Polygon(4);
		pBackFace->SetVertex(0, Vertex(-halfWidth, -halfHeight, +halfDepth));
		pBackFace->SetVertex(1, Vertex(+halfWidth, -halfHeight,	+halfDepth));
		pBackFace->SetVertex(2, Vertex(+halfWidth, +halfHeight, +halfDepth));
		pBackFace->SetVertex(3, Vertex(-halfWidth, +halfHeight, +halfDepth));
		SetPolygon(2, pBackFace);
		Polygon* pBottomFace = new Polygon(4);
		pBottomFace->SetVertex(0, Vertex(-halfWidth, -halfHeight, -halfDepth));
		pBottomFace->SetVertex(1, Vertex(+halfWidth, -halfHeight, -halfDepth));
		pBottomFace->SetVertex(2, Vertex(+halfWidth, -halfHeight, +halfDepth));
		pBottomFace->SetVertex(3, Vertex(-halfWidth, -halfHeight, +halfDepth));
		SetPolygon(3, pBottomFace);
		Polygon* pLeftFace = new Polygon(4);
		pLeftFace->SetVertex(0, Vertex(-halfWidth, +halfHeight, +halfDepth));
		pLeftFace->SetVertex(1, Vertex(-halfWidth, +halfHeight, -halfDepth));
		pLeftFace->SetVertex(2, Vertex(-halfWidth, -halfHeight, -halfDepth));
		pLeftFace->SetVertex(3, Vertex(-halfWidth, -halfHeight, +halfDepth));
		SetPolygon(4, pLeftFace);
		Polygon* pRightFace = new Polygon(4);
		pRightFace->SetVertex(0, Vertex(+halfWidth, +halfHeight, -halfDepth));
		pRightFace->SetVertex(1, Vertex(+halfWidth, +halfHeight, +halfDepth));
		pRightFace->SetVertex(2, Vertex(+halfWidth, -halfHeight, +halfDepth));
		pRightFace->SetVertex(3, Vertex(+halfWidth, -halfHeight, -halfDepth));
		SetPolygon(5, pRightFace);
	}

	CubeMesh::~CubeMesh() {

	}
}