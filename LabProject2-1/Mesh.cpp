
#include "stdafx.h"
#include "Mesh.h"
#include "GraphicsPipeline.h"


void Draw2DLine(HDC hDCFrameBuffer, _3DLab::Point3D& previousProject,
	_3DLab::Point3D& currentProject) {
	// 투영 좌표계의 2점을 화면 좌표계로 변환하고
	// 변환된 두 점(픽셀)을 선분으로 그림
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
	// 메쉬의 다각형 설정
		if ((0 <= indexNumber) && (indexNumber < m_polygonsNumber)) {
			m_ppPolygons[indexNumber] = pPolygon;
		}
	}

	/*
	 * 첫번째 for문 j와 i를 사용한 이유는 m_ptrToPolygons가 이중 포인터임
	 * 첫번째 vertex를 따로 처리해 주는 이유는 polygons 중에 점이 있다면
	 * numberOfVertices 가 1이 되므로 for문을 생략하게 됨
	 * initialProject가 설정되지 않아서
	 * 예외 발생으로 크래시가 일어나기 때문
	 */
	void Mesh::Render(HDC hDCFrameBuffer) {
		Point3D initialProject, previousProject, intersect;
		bool previousInside = false, initialInside = false,
			currentInside = false, intersectInside = false;

		// 메쉬를 구성하는 모든 polygons 렌더링
		for (int j = 0; j < m_polygonsNumber; ++j) {
			int numberOfVertices = m_ppPolygons[j]->m_verticesNumber;
			Vertex* vertices = m_ppPolygons[j]->m_pVertices;

			// 다각형의 첫번째 vertex를 원근 투영 변환한다
			previousProject = initialProject =
				GraphicsPipeline::Project(vertices[0].m_position);

			// 변환된 점이 투영 사각형에 포함되는지 계산
			previousInside = initialInside =
				(-1.f <= initialProject.x) && (initialProject.x <= 1.f)
				&& (-1.f <= initialProject.y) && (initialProject.y <= 1.f);

			// 다각형을 구성하는 모든 정점들을 원근 투영 변환하고 선분으로 렌더링
			for (int i = 1; i < numberOfVertices; ++i) {
				Point3D currentProject = GraphicsPipeline::Project(vertices[i].m_position);
				// 원근 투영된 점이 투영 사각형에 포함되는지 계산
				currentInside =
					(-1.f <= currentProject.x) && (currentProject.x <= 1.f)
					&& (-1.f <= currentProject.y) && (currentProject.y <= 1.f);
				// 원근 투영된 점이 투영 사각형에 포함되면 이전 점과 현재 점을 선분으로 그림
				if (((previousProject.z >= 0.f) || (currentProject.z >= 0.f))
					&& (previousInside || currentInside)) {
					::Draw2DLine(hDCFrameBuffer, previousProject, currentProject);
				}
				previousProject = currentProject;
				previousInside = currentInside;
				// 다각형의 마지막 vertex와 첫번째 vertex를 선분으로 그림
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