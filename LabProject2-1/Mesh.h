

#pragma once

namespace _3DLab {
	// A struct have three float points represent position
	struct Point3D {
		Point3D() {}
		Point3D(float x, float y, float z)
			: x(x), y(y), z(z) {}
		virtual ~Point3D() {}

		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
	};

	struct Vertex {
		Vertex() { }
		Vertex(float x, float y, float z)
			: m_position(Point3D{ x, y, z }) {}
		virtual ~Vertex() { }

		Point3D m_position;
	};

	struct Polygon {
		Polygon() { }
		Polygon(int verticesNumber);
		virtual ~Polygon();

		//�ٰ���(��)�� �����ϴ� �������� ����Ʈ�̴�.
		int m_verticesNumber = 0;
		Vertex* m_pVertices = nullptr;
		void SetVertex(int indexNumber, Vertex vertex);
	};


	class Mesh {
	public:
		Mesh() {}
		Mesh(int polygonsNumber);
		virtual ~Mesh();

	private:
		// �ν��Ͻ��� ���Ͽ� �޽��� ���� ��ü�鿡 ������ �� �ִ�
		// ���� �������� �޽��� �����Ǵ� ���� ��ü�� ����
		int m_referenceNumber = 1;

	public:
		// �޽��� ���� ��ü�� ������ ������ �������� 1�� ����
		void AddRef() { ++m_referenceNumber; }
		// �޽��� �����ϴ� ���� ��ü�� �Ҹ�� ������ �������� 1�� ����
		// �������� 0�̵Ǹ� �޽��� �Ҹ��Ų��
		// �̺κ� �׽�Ʈ�غ���
		void Release() {
			--m_referenceNumber;
			if (m_referenceNumber <= 0) {
				delete this;
			}
		}

	private:
		int m_polygonsNumber = 0;
		// pointing to polygon pointer array
		// *[polygon*]
		Polygon** m_ppPolygons = nullptr;

	public:
		void SetPolygon(int indexNumber, Polygon* ptrToPolygon);

		// �޽� ������
		virtual void Render(HDC hDCFrameBuffer);
	};

	class CubeMesh : public Mesh {
	public:
		CubeMesh(float width = 4.f, float height = 4.f, float depth = 4.f);
		virtual ~CubeMesh();
	};

}