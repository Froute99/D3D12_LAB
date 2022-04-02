
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
	::MoveToEx(hDCFrameBuffer, (long)previous.x, (long)previous.y, NULL);
	::LineTo(hDCFrameBuffer, (long)current.x, (long)current.y);
}

namespace _3DLab {
	Polygon::Polygon(int verticesNumber) {
		this->m_verticesNumber = verticesNumber;
		m_pVertices = new Vertex[this->m_verticesNumber];
	}

	Polygon::~Polygon() {
		if (m_pVertices) {
			delete[] m_pVertices;
		}
	}

	// i think parameter vertex should be const reference
	void Polygon::SetVertex(int indexNumber, Vertex vertex) {
		if ((0 <= indexNumber) && (indexNumber < m_verticesNumber) && m_pVertices) {
			m_pVertices[indexNumber] = vertex;
		}
	}

	Mesh::Mesh(int polygonsNumber) {
		m_polygonsNumber = polygonsNumber;
		m_ppPolygons = new Polygon* [polygonsNumber];
	}

	Mesh::~Mesh() {
		if (m_ppPolygons) {
			for (int i = 0; i < m_polygonsNumber; ++i) {
				if (m_ppPolygons[i]) {
					delete m_ppPolygons[i];
				}
				delete[] m_ppPolygons;
			}
		}
	}

	void Mesh::SetPolygon(int indexNumber, Polygon* pPolygon) {
	// �޽��� �ٰ��� ����
		if ((0 <= indexNumber) && (indexNumber < m_polygonsNumber)) {
			m_ppPolygons[indexNumber] = pPolygon;
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
		for (int j = 0; j < m_polygonsNumber; ++j) {
			int numberOfVertices = m_ppPolygons[j]->m_verticesNumber;
			Vertex* vertices = m_ppPolygons[j]->m_pVertices;

			// �ٰ����� ù��° vertex�� ���� ���� ��ȯ�Ѵ�
			previousProject = initialProject =
				GraphicsPipeline::Project(vertices[0].m_position);

			// ��ȯ�� ���� ���� �簢���� ���ԵǴ��� ���
			previousInside = initialInside =
				(-1.f <= initialProject.x) && (initialProject.x <= 1.f)
				&& (-1.f <= initialProject.y) && (initialProject.y <= 1.f);

			// �ٰ����� �����ϴ� ��� �������� ���� ���� ��ȯ�ϰ� �������� ������
			for (int i = 1; i < numberOfVertices; ++i) {
				Point3D currentProject = GraphicsPipeline::Project(vertices[i].m_position);
				// ���� ������ ���� ���� �簢���� ���ԵǴ��� ���
				currentInside =
					(-1.f <= currentProject.x) && (currentProject.x <= 1.f)
					&& (-1.f <= currentProject.y) && (currentProject.y <= 1.f);
				// ���� ������ ���� ���� �簢���� ���ԵǸ� ���� ���� ���� ���� �������� �׸�
				if (((previousProject.z >= 0.f) || (currentProject.z >= 0.f))
					&& (previousInside || currentInside)) {
					::Draw2DLine(hDCFrameBuffer, previousProject, currentProject);
				}
				previousProject = currentProject;
				previousInside = currentInside;
				// �ٰ����� ������ vertex�� ù��° vertex�� �������� �׸�
			}

			if (((previousProject.z >= 0.f) || (initialProject.z >= 0.f))
				&& (initialInside || previousInside)) {
				::Draw2DLine(hDCFrameBuffer, previousProject, initialProject);
			}
		}
	}

	CubeMesh::CubeMesh(float width, float height, float depth)
		: Mesh(6) {
		float halfWidth = width * 0.5f;
		float halfHeight = height * 0.5f;
		float halfDepth = depth * 0.5f;

		Polygon* pFrontFace = new Polygon(4);
		pFrontFace->SetVertex(0, Vertex(-halfWidth, +halfHeight, -halfDepth));
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

	CubeMesh::~CubeMesh() {}
}