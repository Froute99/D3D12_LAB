// 정점 셰이더를 정의한다. 렌더 타겟 사각형 전체를 삼각형 2개로 표현한다.
float4 VSMain(uint nVertexID : SV_VertexID) : SV_POSITION
{
	float4 output = (float4)0;

	if (nVertexID == 0) output = float4(-1.0f, +1.0f, 0.0f, 1.0f);
	else if (nVertexID == 1) output = float4(+1.0f, +1.0f, 0.0f, 1.0f);
	else if (nVertexID == 2) output = float4(+1.0f, -1.0f, 0.0f, 1.0f);

	else if (nVertexID == 3) output = float4(-1.0f, +1.0f, 0.0f, 1.0f);
	else if (nVertexID == 4) output = float4(+1.0f, -1.0f, 0.0f, 1.0f);
	else if (nVertexID == 5) output = float4(-1.0f, -1.0f, 0.0f, 1.0f);

	return output;
}


#define FRAME_BUFFER_WIDTH		800.0f
#define FRAME_BUFFER_HEIGHT		600.0f

float4 PSMain(float4 input : SV_POSITION) : SV_TARGET
{
	float4 cColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	float2 f2NDC = float2(input.x / FRAME_BUFFER_WIDTH,
		input.y / FRAME_BUFFER_HEIGHT) - 0.5f;
	f2NDC.x *= (FRAME_BUFFER_WIDTH / FRAME_BUFFER_HEIGHT);

	float fRadius = 0.3f;
	float fRadian = radians(360.0f / 30.0f);
	for (float f = 0; f < 30.0f; f += 1.0f) {
		float fAngle = fRadian * f;
		cColor.rgb += (0.0025f / length(f2NDC + float2(fRadius * cos(fAngle),
			fRadius * sin(fAngle))));
	}

	return cColor;
}
