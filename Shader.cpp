// Shader.cpp
#include "stdafx.h"
#include "Shader.h"
#include "Player.h"
#include <algorithm>

CShader::CShader()
{

}

CShader::~CShader()
{
	if (m_ppd3dPipelineStates)
	{
		for (int i = 0; i < m_nPipelineStates; i++) if (m_ppd3dPipelineStates[i])
			m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
}

// 래스터라이저 상태를 설정하기 위한 구조체를 반환
D3D12_RASTERIZER_DESC CShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	//d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;  // 은면 제거 함
	 //d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_NONE; // 은면 제거 안함
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	return(d3dRasterizerDesc);
}

// 깊이-스텐실 검사를 위한 상태를 설정하기 위한 구조체를 반환
D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	return(d3dDepthStencilDesc);
}

// 블렌딩 상태를 설정하기 위한 구조체를 반환
D3D12_BLEND_DESC CShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	return(d3dBlendDesc);
}

// 입력 조립기에게 정점 버퍼의 구조를 알려주기 위한 구조체를 반환
D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;

	return(d3dInputLayoutDesc);
}

// 정점 셰이더 바이트 코드를 생성(컴파일)
D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

// 픽셀 셰이더 바이트 코드를 생성(컴파일)
D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

// 셰이더 소스 코드를 컴파일하여 바이트 코드 구조체를 반환
D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(const WCHAR* pszFileName, LPCSTR
	pszShaderName, LPCSTR pszShaderProfile, ID3DBlob** ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	::D3DCompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderProfile,
		nCompileFlags, 0, ppd3dShaderBlob, NULL);
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();
	return(d3dShaderByteCode);
}

// 그래픽스 파이프라인 상태 객체를 생성 
void CShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature * pd3dGraphicsRootSignature)
{
	ID3DBlob* pd3dVertexShaderBlob = NULL, * pd3dPixelShaderBlob = NULL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc,
		__uuidof(ID3D12PipelineState), (void**)&m_ppd3dPipelineStates[0]);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();

	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[]
		d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
	// 파이프라인에 그래픽스 상태 객체를 설정 
	pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
}

void CShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	OnPrepareRender(pd3dCommandList);
}

void CShader::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
}
void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList* pd3dCommandList, XMFLOAT4X4* pxmf4x4World)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(pxmf4x4World)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}

void CShader::ReleaseShaderVariables()
{
}

CPlayerShader::CPlayerShader()
{
}
CPlayerShader::~CPlayerShader()
{
}

// 셰이더 마다 다른 입력 구조를 갖게 하기 위해 
// Diffuse 셰이더는 정점 버퍼를 쓰니까 자기한테 맞는 Input Layout을 직접 제공
D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

// 부모는 파이프라인 만드는 방법을 알고 있고(실제 쉐이더 생성),
// 자식은 어떤 셰이더를 쓸지만
void CPlayerShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

CObjectsShader::CObjectsShader()
{
}
CObjectsShader::~CObjectsShader()
{
}

// 정점 버퍼에 정점 데이터가 어떤 구조로 저장되어 있는지(입력 레이아웃를 GPU에게 알려주는 함수
D3D12_INPUT_LAYOUT_DESC CObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	// "POSITION", "COLOR" -> 시맨틱, hlsl 코드 이름과 일치
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1", ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1", ppd3dShaderBlob));
}

// PSO 생성 준비과정 "나는 PipelineState를 몇 개 사용할 거고, 그걸 저장할 배열을 만들겠다"
void CObjectsShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

// 쉐이더 내의 오브젝트들 생성
void CObjectsShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	// 육면체 벽 메쉬 생성
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		150.0f, 100.0f, 150.0f, XMFLOAT4(0.7f, 0.9f, 1.0f, 1.0f));
	CCubeMeshDiffused* pStage2WallMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		150.0f, 100.0f, 150.0f, XMFLOAT4(1.0f, 0.8f, 0.6f, 1.0f));

	m_pWallMeshStage1 = pCubeMesh;
	m_pWallMeshStage2 = pStage2WallMesh;
	m_pWallMeshStage1->AddRef();
	m_pWallMeshStage2->AddRef();

	// 도착 지점 메쉬 생성
	CCubeMeshDiffused* pGoalMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f, 
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	// 파편 메쉬 생성
	m_pFragmentMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 8.0f, 8.0f, 8.0f, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	float floorThickness = 20.0f;
	float floorStepHeight = 20.0f;

	// 바닥 메쉬 생성
	CCubeMeshDiffused* pFloorMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		150.0f, floorThickness, 150.0f, XMFLOAT4(1.0f, 0.8f, 0.6f, 1.0f));
	CCubeMeshDiffused* pStage2FloorMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		150.0f, floorThickness, 150.0f, XMFLOAT4(0.7f, 0.9f, 1.0f, 1.0f));
	m_pFloorMeshStage1 = pFloorMesh;
	m_pFloorMeshStage2 = pStage2FloorMesh;
	m_pFloorMeshStage1->AddRef();
	m_pFloorMeshStage2->AddRef();

	BuildMazeMap();   // 미로 생성
	BuildFloorMap();  // 바닥 생성
	BuildEnemies(pd3dDevice, pd3dCommandList); // 적 생성
	BuildCrossHair(pd3dDevice, pd3dCommandList); // 조준점 생성

	const int wallHeight = 3;

	float fxPitch = 150.0f;
	float fyPitch = 100.0f;
	float fzPitch = 150.0f;

	const int enemyCount = 7;

	// 바닥 MAZE_X * MAZE_Z개 + 벽 최대 개수 + 도착 지점 1개
	int maxObjects = (MAZE_X * MAZE_Z) + (MAZE_X * MAZE_Z * wallHeight) + 1 + enemyCount;
	m_ppObjects = new CGameObject * [maxObjects];

	int i = 0;

	// 바닥 생성
	for (int z = 0; z < MAZE_Z; z++)
	{
		for (int x = 0; x < MAZE_X; x++)
		{
			CGameObject* pFloor = new CGameObject();
			pFloor->SetMesh(pFloorMesh);

			float floorY = 0.0f;

			// 길인 칸만 단차 적용
			if (m_Maze[z][x] == 0)
			{
				floorY = m_Floor[z][x] * floorStepHeight;
			}

			pFloor->SetPosition(
				fxPitch * x,
				floorY - floorThickness * 0.5f,
				fzPitch * z
			);

			m_ppObjects[i++] = pFloor;
		}
	}

	// 벽 생성
	m_nWallObjectStartIndex = i;
	for (int z = 0; z < MAZE_Z; z++)
	{
		for (int x = 0; x < MAZE_X; x++)
		{
			if (m_Maze[z][x] == 1)
			{
				// 벽은 항상 기본 높이
				float floorY = 0.0f;

				for (int y = 0; y < wallHeight; y++)
				{
					CRotatingObject* pWall = new CRotatingObject();
					pWall->SetMesh(pCubeMesh);

					pWall->SetPosition(
						fxPitch * x,
						floorY + fyPitch * y,
						fzPitch * z
					);

					pWall->SetBoundingBox(
						XMFLOAT3(fxPitch * x, floorY + fyPitch * y, fzPitch * z),
						XMFLOAT3(75.0f, 50.0f, 75.0f)
					);

					pWall->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
					pWall->SetRotationSpeed(0.0f);

					m_ppObjects[i++] = pWall;
				}
			}
		}
	}


	m_nWallObjectCount = i - m_nWallObjectStartIndex;

	// 도착 지점 큐브
	CGameObject* pGoal = new CGameObject();
	pGoal->SetMesh(pGoalMesh);

	float goalY = m_Floor[9][9] * floorStepHeight;

	pGoal->SetPosition(fxPitch * 9, goalY + 6.0f, fzPitch * 9);

	m_ppObjects[i++] = pGoal;

	m_nObjects = i;

	BuildGameStateObjects(pd3dDevice, pd3dCommandList);  // 게임 상태 UI 오브젝트 생성
	BuildStartStageObjects(pd3dDevice, pd3dCommandList); // 0스테이지 시작 화면 생성

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}
	for (int i = 0; i < (int)m_vEnemies.size(); i++)
	{
		delete m_vEnemies[i];
	}
	m_vEnemies.clear();

	for (int i = 0; i < (int)m_vGameOverObjects.size(); i++)
	{
		delete m_vGameOverObjects[i];
	}
	m_vGameOverObjects.clear();

	for (int i = 0; i < (int)m_vGameClearObjects.size(); i++)
	{
		delete m_vGameClearObjects[i];
	}
	m_vGameClearObjects.clear();

	for (int i = 0; i < (int)m_vStartStageObjects.size(); i++)
	{
		delete m_vStartStageObjects[i];
	}
	m_vStartStageObjects.clear();

	for (int i = 0; i < (int)m_vStage1SelectObjects.size(); i++)
	{
		delete m_vStage1SelectObjects[i];
	}
	m_vStage1SelectObjects.clear();

	for (int i = 0; i < (int)m_vStage2SelectObjects.size(); i++)
	{
		delete m_vStage2SelectObjects[i];
	}
	m_vStage2SelectObjects.clear();
	if (m_pWallMeshStage1) m_pWallMeshStage1->Release();
	if (m_pWallMeshStage2) m_pWallMeshStage2->Release();
	m_pWallMeshStage1 = NULL;
	m_pWallMeshStage2 = NULL;
}

void CObjectsShader::AnimateObjects(float fTimeElapsed, CPlayer* pPlayer)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}

	const float detectDistance = 800.0f;

	// 적 이동
	if (pPlayer)
	{
		XMFLOAT3 playerPos = pPlayer->GetPosition();

		for (CEnemyObject* pEnemy : m_vEnemies)
		{
			if (!pEnemy) continue;

			XMFLOAT3 enemyPos = pEnemy->GetPosition();

			float dx = playerPos.x - enemyPos.x;
			float dz = playerPos.z - enemyPos.z;

			float distance = sqrtf(dx * dx + dz * dz);

			// 감지 거리 밖이면 이동하지 않음
			if (distance > detectDistance) continue;

			// 적이 이동하고 싶은 방향 벡터 계산
			XMFLOAT3 move = pEnemy->GetMoveToPlayerVector(playerPos, fTimeElapsed);

			XMFLOAT3 oldPos = pEnemy->GetPosition();

			// X축 이동
			pEnemy->SetPosition(oldPos.x + move.x, oldPos.y, oldPos.z);

			if (CheckObjectCollision(pEnemy))
				pEnemy->SetPosition(oldPos);

			// Z축 이동
			oldPos = pEnemy->GetPosition();

			pEnemy->SetPosition(oldPos.x, oldPos.y, oldPos.z + move.z);

			if (CheckObjectCollision(pEnemy))
				pEnemy->SetPosition(oldPos);

			// 바닥 단차 맞추기
			enemyPos = pEnemy->GetPosition();
			float floorY = GetFloorHeight(enemyPos.x, enemyPos.z);
			float targetY = floorY + 50.0f;
			float t = 15.0f * fTimeElapsed;
			if (t > 1.0f) t = 1.0f;
			enemyPos.y = enemyPos.y + (targetY - enemyPos.y) * t;

			pEnemy->SetPosition(enemyPos);
		}
	}

	// 총알 이동
	for (CBulletObject* pBullet : m_vBullets)
	{
		if (pBullet) pBullet->Animate(fTimeElapsed);
	}

	// 총알, 적 충돌 검사
	for (CBulletObject* pBullet : m_vBullets)
	{
		if (!pBullet || pBullet->IsDead()) continue;

		for (CEnemyObject* pEnemy : m_vEnemies)
		{
			if (!pEnemy) continue;

			if (pBullet->GetBoundingBox().Intersects(pEnemy->GetBoundingBox()))
			{
				CreateFragments(pEnemy->GetPosition());

				pBullet->SetDead(true);
				pEnemy->SetDead(true);

				break;
			}
		}
	}

	for (CFragmentObject* pFragment : m_vFragments)
	{
		if (pFragment) pFragment->Animate(fTimeElapsed);
	}

	// 죽은 적 제거
	for (int i = 0; i < (int)m_vEnemies.size(); )
	{
		CEnemyObject* pEnemy = m_vEnemies[i];
		if (pEnemy && pEnemy->IsDead())
		{
			delete pEnemy;
			m_vEnemies.erase(m_vEnemies.begin() + i);
		}
		else
		{
			i++;
		}
	}

	// 죽은 총알 제거
	for (int i = 0; i < (int)m_vBullets.size(); )
	{
		CBulletObject* pBullet = m_vBullets[i];
		if (pBullet && pBullet->IsDead())
		{
			delete pBullet;
			m_vBullets.erase(m_vBullets.begin() + i);
		}
		else
		{
			i++;
		}
	}

	// 사라진 파편 제거
	for (int i = 0; i < (int)m_vFragments.size(); )
	{
		CFragmentObject* pFragment = m_vFragments[i];
		if (pFragment && pFragment->IsDead())
		{
			delete pFragment;
			m_vFragments.erase(m_vFragments.begin() + i);
		}
		else
		{
			i++;
		}
	}
	UpdateGun(pPlayer);
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

void CObjectsShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera, bool bGameOver,
	bool bGameClear, bool bStartStage, int nSelectedStage)
{
	CShader::Render(pd3dCommandList, pCamera);

	// 시작화면이면 시작화면 오브젝트만 그리고, 실제 게임 오브젝트는 그리지 않는다.
	if (bStartStage)
	{
		for (int i = 0; i < (int)m_vStartStageObjects.size(); i++)
		{
			CGameObject* pObject = m_vStartStageObjects[i];
			if (pObject)
			{
				pObject->Render(pd3dCommandList, pCamera);
			}
		}

		// 선택된 스테이지에 따라 빨간 테두리를 그릴 목록을 고른다.
		std::vector<CGameObject*>* pvSelectedObjects = NULL;
		if (nSelectedStage == 2)
		{
			pvSelectedObjects = &m_vStage2SelectObjects;
		}
		else
		{
			pvSelectedObjects = &m_vStage1SelectObjects;
		}

		for (int i = 0; i < (int)pvSelectedObjects->size(); i++)
		{
			CGameObject* pObject = (*pvSelectedObjects)[i];
			if (pObject)
			{
				pObject->Render(pd3dCommandList, pCamera);
			}
		}
		return;
	}

	// 게임 오버 화면이면 게임 오버 표시만 그린다.
	if (bGameOver)
	{
		for (int i = 0; i < (int)m_vGameOverObjects.size(); i++)
		{
			CGameObject* pObject = m_vGameOverObjects[i];
			if (pObject)
			{
				pObject->Render(pd3dCommandList, pCamera);
			}
		}
		return;
	}

	// 게임 클리어 화면이면 게임 클리어 표시만 그린다.
	if (bGameClear)
	{
		for (int i = 0; i < (int)m_vGameClearObjects.size(); i++)
		{
			CGameObject* pObject = m_vGameClearObjects[i];
			if (pObject)
			{
				pObject->Render(pd3dCommandList, pCamera);
			}
		}
		return;
	}

	// 여기부터는 실제 플레이 중에 보이는 오브젝트들이다.
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}

	for (int i = 0; i < (int)m_vEnemies.size(); i++)
	{
		CEnemyObject* pEnemy = m_vEnemies[i];
		if (pEnemy)
		{
			pEnemy->Render(pd3dCommandList, pCamera);
		}
	}

	for (int i = 0; i < (int)m_vBullets.size(); i++)
	{
		CBulletObject* pBullet = m_vBullets[i];
		if (pBullet)
		{
			pBullet->Render(pd3dCommandList, pCamera);
		}
	}

	if (m_pGun)
	{
		m_pGun->Render(pd3dCommandList, pCamera);
	}

	for (int i = 0; i < (int)m_vFragments.size(); i++)
	{
		CFragmentObject* pFragment = m_vFragments[i];
		if (pFragment)
		{
			pFragment->Render(pd3dCommandList, pCamera);
		}
	}

	// 1인칭일 때만 Crosshair 갱신 + 렌더
	if (pCamera && pCamera->GetMode() == FIRST_PERSON_CAMERA)
	{
		UpdateCrossHair(pCamera);

		if (m_pCrossHairH) m_pCrossHairH->Render(pd3dCommandList, pCamera);
		if (m_pCrossHairV) m_pCrossHairV->Render(pd3dCommandList, pCamera);
	}
}
// 미로 맵 만들기	, 0이면 빈 공간, 1이면 벽
void CObjectsShader::BuildMazeMap(int nStage)
{
	if (nStage == 2)
		BuildStage2MazeMap();
	else
		BuildStage1MazeMap();
}

void CObjectsShader::BuildStage1MazeMap()
{
	int maze[MAZE_Z][MAZE_X] =
	{
		{1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,1,0,0,0,1},
		{1,0,1,1,1,0,1,0,1,0,1},
		{1,0,1,0,0,0,0,0,1,0,1},
		{1,0,1,0,1,1,1,0,1,0,1},
		{1,0,0,0,1,0,0,0,1,0,1},
		{1,1,1,0,1,0,1,1,1,0,1},
		{1,0,0,0,1,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1}
	};

	memcpy(m_Maze, maze, sizeof(maze));
}

void CObjectsShader::BuildStage2MazeMap()
{
	int maze[MAZE_Z][MAZE_X] =
	{
		{1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,1,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,1,1,0,1},
		{1,0,1,0,0,0,0,0,1,0,1},
		{1,0,1,1,1,1,1,0,1,0,1},
		{1,0,0,0,0,0,1,0,0,0,1},
		{1,1,1,1,1,0,1,0,1,0,1},
		{1,0,0,0,1,0,0,0,1,0,1},
		{1,0,1,0,1,0,1,0,1,0,1},
		{1,0,1,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1}
	};

	memcpy(m_Maze, maze, sizeof(maze));
}

// 바닥 높이 만들기, 숫자가 클수록 높은 바닥
void CObjectsShader::BuildFloorMap()
{
	int floor[MAZE_Z][MAZE_X] =
	{
		{0,0,0,1,1,0,0,1,0,0,0},
		{0,0,1,1,2,1,0,1,1,0,0},
		{0,0,1,2,2,1,1,2,1,0,0},
		{0,1,1,2,3,2,2,2,1,1,0},
		{0,0,1,2,2,2,1,2,2,1,0},
		{0,0,0,1,2,1,1,2,1,1,0},
		{0,1,0,1,1,1,0,1,1,2,0},
		{0,1,1,1,0,1,1,1,2,2,0},
		{0,0,1,0,0,1,0,1,1,2,0},
		{0,0,0,0,1,1,1,0,1,1,0},
		{0,0,0,0,0,1,0,0,0,0,0}
	};

	memcpy(m_Floor, floor, sizeof(floor));
}

void CObjectsShader::ApplyStageMap(int nStage)
{
	BuildMazeMap(nStage);

	const int wallHeight = 3;
	float fxPitch = 150.0f;
	float fyPitch = 100.0f;
	float fzPitch = 150.0f;
	float floorThickness = 20.0f;
	float floorStepHeight = 20.0f;

	CMesh* pFloorMesh = NULL;
	if (nStage == 2)
	{
		pFloorMesh = m_pFloorMeshStage2;
	}
	else
	{
		pFloorMesh = m_pFloorMeshStage1;
	}

	for (int z = 0; z < MAZE_Z; z++)
	{
		for (int x = 0; x < MAZE_X; x++)
		{
			int objectIndex = z * MAZE_X + x;
			if (!m_ppObjects[objectIndex]) continue;

			m_ppObjects[objectIndex]->SetMesh(pFloorMesh);

			float floorY = 0.0f;
			if (m_Maze[z][x] == 0)
				floorY = m_Floor[z][x] * floorStepHeight;

			m_ppObjects[objectIndex]->SetPosition(
				fxPitch * x,
				floorY - floorThickness * 0.5f,
				fzPitch * z
			);
		}
	}

	int wallObjectIndex = m_nWallObjectStartIndex;
	CMesh* pWallMesh = NULL;
	if (nStage == 2)
	{
		pWallMesh = m_pWallMeshStage2;
	}
	else
	{
		pWallMesh = m_pWallMeshStage1;
	}

	for (int z = 0; z < MAZE_Z; z++)
	{
		for (int x = 0; x < MAZE_X; x++)
		{
			if (m_Maze[z][x] != 1) continue;

			for (int y = 0; y < wallHeight; y++)
			{
				if (wallObjectIndex >= (m_nWallObjectStartIndex + m_nWallObjectCount)) return;
				if (!m_ppObjects[wallObjectIndex]) continue;

				CGameObject* pWall = m_ppObjects[wallObjectIndex++];
				pWall->SetMesh(pWallMesh);
				pWall->SetPosition(fxPitch * x, fyPitch * y, fzPitch * z);
				pWall->SetBoundingBox(
					XMFLOAT3(fxPitch * x, fyPitch * y, fzPitch * z),
					XMFLOAT3(75.0f, 50.0f, 75.0f)
				);
			}
		}
	}

	int goalIndex = m_nWallObjectStartIndex + m_nWallObjectCount;
	if (goalIndex < m_nObjects && m_ppObjects[goalIndex])
	{
		float goalY = m_Floor[9][9] * floorStepHeight;
		m_ppObjects[goalIndex]->SetPosition(fxPitch * 9, goalY + 6.0f, fzPitch * 9);
	}
}

// 충돌 검사 함수
bool CObjectsShader::CheckObjectCollision(CGameObject* pObject)
{
	if (!pObject) return false;
	if (!pObject->HasBoundingBox()) return false;

	BoundingBox objectBox = pObject->GetBoundingBox();

	for (int i = 0; i < m_nObjects; i++)
	{
		if (!m_ppObjects[i]) continue;
		if (!m_ppObjects[i]->HasBoundingBox()) continue;

		BoundingBox wallBox = m_ppObjects[i]->GetBoundingBox();

		if (objectBox.Intersects(wallBox))
		{
			return true;
		}
	}

	return false;
}

// 바닥 높이 함수
float CObjectsShader::GetFloorHeight(float x, float z)
{
	const float cellSize = 150.0f;
	const float floorStepHeight = 20.0f;

	int mazeX = (int)((x + cellSize * 0.5f) / cellSize);
	int mazeZ = (int)((z + cellSize * 0.5f) / cellSize);

	if (mazeX < 0 || mazeX >= MAZE_X) return 0.0f;
	if (mazeZ < 0 || mazeZ >= MAZE_Z) return 0.0f;

	if (m_Maze[mazeZ][mazeX] == 1) return 0.0f;

	return m_Floor[mazeZ][mazeX] * floorStepHeight;
}

// 적 생성
void CObjectsShader::BuildEnemies(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	CCubeMeshDiffused* pEnemyMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		40.0f, 100.0f, 40.0f, 
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	// 적 7마리 초기 위치
	XMFLOAT3 enemyPositions[] =
	{
		XMFLOAT3(150.0f * 1, 60.0f, 150.0f * 4),
		XMFLOAT3(150.0f * 5, 60.0f, 150.0f * 1),
		XMFLOAT3(150.0f * 7, 60.0f, 150.0f * 3),
		XMFLOAT3(150.0f * 3, 60.0f, 150.0f * 5),
		XMFLOAT3(150.0f * 5, 60.0f, 150.0f * 7),
		XMFLOAT3(150.0f * 8, 60.0f, 150.0f * 9),
		XMFLOAT3(150.0f * 9, 60.0f, 150.0f * 9)
	};

	for (auto& pos : enemyPositions)
	{
		CEnemyObject* pEnemy = new CEnemyObject();
		pEnemy->SetMesh(pEnemyMesh);
		pEnemy->SetPosition(pos);
		pEnemy->SetBoundingBox(pos, XMFLOAT3(20.0f, 50.0f, 20.0f));
		pEnemy->SetMoveSpeed(60.0f);

		m_vEnemies.push_back(pEnemy);
	}

	BuildGunAndBulletMesh(pd3dDevice, pd3dCommandList);
}

void CObjectsShader::ShootBullet(CPlayer* pPlayer, CCamera* pCamera)
{
	if (!pPlayer || !pCamera || !m_pBulletMesh) return;

	CBulletObject* pBullet = new CBulletObject();
	pBullet->SetMesh(m_pBulletMesh);

	XMFLOAT3 startPos;
	XMFLOAT3 dir;
	XMFLOAT3 bulletPos;

	if (pCamera && pCamera->GetMode() == THIRD_PERSON_CAMERA)
	{
		startPos = pPlayer->GetPosition();
		dir = pPlayer->GetLookVector();

		bulletPos = XMFLOAT3(
			startPos.x + dir.x * 30.0f,
			startPos.y + 20.0f,
			startPos.z + dir.z * 30.0f
		);
	}
	else
	{
		startPos = pCamera->GetPosition();
		dir = pCamera->GetLookVector();

		bulletPos = XMFLOAT3(
			startPos.x + dir.x * 30.0f,
			startPos.y + dir.y * 30.0f,
			startPos.z + dir.z * 30.0f
		);
	}

	pBullet->SetPosition(bulletPos);
	pBullet->SetBoundingBox(bulletPos, XMFLOAT3(5.0f, 5.0f, 5.0f));
	pBullet->SetDirection(dir);

	m_vBullets.push_back(pBullet);
}

void CObjectsShader::BuildGunAndBulletMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	CCubeMeshDiffused* pGunMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		20.0f, 20.0f, 20.0f,
		XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f)
	);

	m_pGun = new CGameObject();
	m_pGun->SetMesh(pGunMesh);

	m_pBulletMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		10.0f, 10.0f, 10.0f,
		XMFLOAT4(1.0f, 0.75f, 0.85f, 1.0f)
	);
}

void CObjectsShader::UpdateGun(CPlayer* pPlayer)
{
	if (!pPlayer || !m_pGun) return;

	XMFLOAT3 pos = pPlayer->GetPosition();
	XMFLOAT3 look = pPlayer->GetLookVector();

	XMFLOAT3 gunPos = XMFLOAT3(
		pos.x + look.x,
		pos.y + 20.0f,
		pos.z + look.z
	);

	m_pGun->SetPosition(gunPos);
	m_pGun->SetLookDirection(look);
}

// 파편 생성
void CObjectsShader::CreateFragments(XMFLOAT3 pos)
{
	for (int i = 0; i < 12; i++)
	{
		CFragmentObject* pFragment = new CFragmentObject();
		pFragment->SetMesh(m_pFragmentMesh);
		pFragment->SetPosition(pos);

		float vx = ((rand() % 200) - 100) * 1.5f;
		float vy = (rand() % 150) + 50.0f;
		float vz = ((rand() % 200) - 100) * 1.5f;

		pFragment->SetVelocity(XMFLOAT3(vx, vy, vz));

		m_vFragments.push_back(pFragment);
	}
}

bool CObjectsShader::CheckGoalCollision(CPlayer* pPlayer)
{
	if (!pPlayer) return false;

	XMFLOAT3 pos = pPlayer->GetPosition();

	float goalX = 150.0f * 9;
	float goalZ = 150.0f * 9;

	float dx = pos.x - goalX;
	float dz = pos.z - goalZ;

	float dist = sqrtf(dx * dx + dz * dz);

	return (dist < 60.0f);
}

bool CObjectsShader::CheckEnemyCollision(CPlayer* pPlayer)
{
	if (!pPlayer) return false;

	BoundingBox playerBox = pPlayer->GetBoundingBox();

	for (CEnemyObject* pEnemy : m_vEnemies)
	{
		if (!pEnemy) continue;

		if (playerBox.Intersects(pEnemy->GetBoundingBox()))
			return true;
	}

	return false;
}

// 게임 상태 UI 오브젝트 생성
void CObjectsShader::BuildGameStateObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	CCubeMeshDiffused* pRedMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		300.0f, 40.0f, 20.0f,
		XMFLOAT4(1.0f, 0.2f, 0.2f, 1.0f)
	);

	CCubeMeshDiffused* pBlueMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		300.0f, 40.0f, 20.0f,
		XMFLOAT4(0.7f, 0.9f, 1.0f, 1.0f)
	);

	// GAME OVER: 빨간 X
	CGameObject* pOver1 = new CGameObject();
	pOver1->SetMesh(pRedMesh);
	pOver1->SetPosition(150.0f * 5, 250.0f, 150.0f * 5);
	pOver1->Rotate(0.0f, 0.0f, 45.0f);
	m_vGameOverObjects.push_back(pOver1);
	CGameObject* pOver2 = new CGameObject();
	pOver2->SetMesh(pRedMesh);
	pOver2->SetPosition(150.0f * 5, 250.0f, 150.0f * 5);
	pOver2->Rotate(0.0f, 0.0f, -45.0f);
	m_vGameOverObjects.push_back(pOver2);

	// GAME CLEAR: 파란 막대 3개
	for (int i = 0; i < 3; i++)
	{
		CGameObject* pClear = new CGameObject();
		pClear->SetMesh(pBlueMesh);
		pClear->SetPosition(150.0f * 5, 200.0f + i * 60.0f, 150.0f * 5);
		m_vGameClearObjects.push_back(pClear);
	}
}

// 시작 화면
void CObjectsShader::BuildStartStageObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	// 1스테이지 버튼
	CCubeMeshDiffused* pStage1ButtonMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 100.0f, 70.0f, 34.0f,
		XMFLOAT4(0.95f, 0.75f, 0.25f, 1.0f)
	);

	// 2스테이지 버튼
	CCubeMeshDiffused* pStage2ButtonMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 100.0f, 70.0f, 34.0f,
		XMFLOAT4(0.95f, 0.75f, 0.25f, 1.0f)
	);

	// 시작 버튼
	CCubeMeshDiffused* pStartButtonMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 200.0f, 70.0f, 34.0f,
		XMFLOAT4(0.35f, 0.65f, 1.0f, 1.0f)
	);

	// 1, 2 막대
	CCubeMeshDiffused* pDigitHMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 52.0f, 8.0f, 8.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CCubeMeshDiffused* pDigitVMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 8.0f, 32.0f, 8.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	// 김은서 막대
	CCubeMeshDiffused* pTitleHMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 48.0f, 7.0f, 7.0f,
		XMFLOAT4(1.0f, 0.75f, 0.85f, 1.0f)
	);

	CCubeMeshDiffused* pTitleVMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 7.0f, 48.0f, 7.0f,
		XMFLOAT4(1.0f, 0.75f, 0.85f, 1.0f)
	);

	CCubeMeshDiffused* pTitleSmallHMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 32.0f, 7.0f, 7.0f,
		XMFLOAT4(1.0f, 0.75f, 0.85f, 1.0f)
	);

	CCubeMeshDiffused* pTitleSmallVMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 7.0f, 32.0f, 7.0f,
		XMFLOAT4(1.0f, 0.75f, 0.85f, 1.0f)
	);

	// START 글자를 만들 때 쓰는 빨간 가로/세로 막대
	CCubeMeshDiffused* pLetterHMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 22.0f, 5.0f, 6.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CCubeMeshDiffused* pLetterVMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 5.0f, 22.0f, 6.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	// 선택된 스테이지 빨간 테두리 막대
	CCubeMeshDiffused* pBorderHMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 118.0f, 8.0f, 8.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CCubeMeshDiffused* pBorderVMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList, 8.0f, 82.0f, 8.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	// 버튼 위치
	float buttonY = -105.0f;
	float buttonZ = 360.0f;
	float digitZ = 332.0f;

	// 제목 위치
	float titleY = 150.0f;
	float titleZ = 332.0f;
	float titleHalfH = 24.0f;
	float titleCharStep = 112.0f;
	float kimX = 26.0f;
	float eunX = kimX + titleCharStep;
	float seoX = eunX + titleCharStep;

	// START 위치
	float startTextY = buttonY - 20.0f;
	float startTextZ = 332.0f;
	float letterTop = 13.0f;
	float letterMid = 0.0f;
	float letterBottom = -13.0f;
	float letterLeft = -10.0f;
	float letterRight = 10.0f;
	float letterStep = 34.0f;
	float textStartX = 82.0f;

	float xS = textStartX;
	float xT1 = textStartX + letterStep;
	float xA = textStartX + letterStep * 2.0f;
	float xR = textStartX + letterStep * 3.0f;
	float xT2 = textStartX + letterStep * 4.0f;

	// 어떤 Mesh를 어느 위치에 놓을지
	struct SStartObjectInfo
	{
		CMesh* pMesh;
		XMFLOAT3 xmf3Position;
	};

	SStartObjectInfo startObjects[] =
	{
		// 김
		{ pTitleHMesh, XMFLOAT3(kimX - 34.0f, titleY + titleHalfH, titleZ) },
		{ pTitleVMesh, XMFLOAT3(kimX - 10.0f, titleY + 4.0f, titleZ) },
		{ pTitleSmallVMesh, XMFLOAT3(kimX + 22.0f, titleY + 10.0f, titleZ) },
		{ pTitleSmallHMesh, XMFLOAT3(kimX - 22.0f, titleY - 16.0f, titleZ) },
		{ pTitleSmallHMesh, XMFLOAT3(kimX - 22.0f, titleY - 42.0f, titleZ) },
		{ pTitleSmallVMesh, XMFLOAT3(kimX - 38.0f, titleY - 29.0f, titleZ) },
		{ pTitleSmallVMesh, XMFLOAT3(kimX - 6.0f, titleY - 29.0f, titleZ) },

		// 은
		{ pTitleSmallHMesh, XMFLOAT3(eunX - 20.0f, titleY + 22.0f, titleZ) },
		{ pTitleSmallHMesh, XMFLOAT3(eunX - 20.0f, titleY - 8.0f, titleZ) },
		{ pTitleSmallVMesh, XMFLOAT3(eunX - 36.0f, titleY + 7.0f, titleZ) },
		{ pTitleSmallVMesh, XMFLOAT3(eunX - 4.0f, titleY + 7.0f, titleZ) },
		{ pTitleHMesh, XMFLOAT3(eunX - 20.0f, titleY - 34.0f, titleZ) },
		{ pTitleSmallVMesh, XMFLOAT3(eunX - 42.0f, titleY - 54.0f, titleZ) },
		{ pTitleHMesh, XMFLOAT3(eunX - 18.0f, titleY - 68.0f, titleZ) },

		// 서
		{ pTitleSmallHMesh, XMFLOAT3(seoX - 30.0f, titleY + 22.0f, titleZ) },
		{ pTitleSmallVMesh, XMFLOAT3(seoX - 42.0f, titleY + 6.0f, titleZ) },
		{ pTitleSmallVMesh, XMFLOAT3(seoX - 18.0f, titleY + 6.0f, titleZ) },
		{ pTitleVMesh, XMFLOAT3(seoX + 28.0f, titleY + 2.0f, titleZ) },
		{ pTitleSmallHMesh, XMFLOAT3(seoX + 10.0f, titleY + 2.0f, titleZ) },

		// 1스테이지, 2스테이지, START
		{ pStage1ButtonMesh, XMFLOAT3(-50.0f, buttonY + 20.0f, buttonZ) },
		{ pStage2ButtonMesh, XMFLOAT3(350.0f, buttonY + 20.0f, buttonZ) },
		{ pStartButtonMesh, XMFLOAT3(150.0f, buttonY - 20.0f, buttonZ) },

		// 1
		{ pDigitVMesh, XMFLOAT3(-50.0f, buttonY + 20.0f, digitZ) },

		// 2
		{ pDigitHMesh, XMFLOAT3(350.0f, buttonY + 42.0f, digitZ) },
		{ pDigitVMesh, XMFLOAT3(372.0f, buttonY + 30.0f, digitZ) },
		{ pDigitHMesh, XMFLOAT3(350.0f, buttonY + 20.0f, digitZ) },
		{ pDigitVMesh, XMFLOAT3(328.0f, buttonY + 10.0f, digitZ) },
		{ pDigitHMesh, XMFLOAT3(350.0f, buttonY - 2.0f, digitZ) },

		// S
		{ pLetterHMesh, XMFLOAT3(xS, startTextY + letterTop, startTextZ) },
		{ pLetterVMesh, XMFLOAT3(xS + letterLeft, startTextY + 7.0f, startTextZ) },
		{ pLetterHMesh, XMFLOAT3(xS, startTextY + letterMid, startTextZ) },
		{ pLetterVMesh, XMFLOAT3(xS + letterRight, startTextY - 7.0f, startTextZ) },
		{ pLetterHMesh, XMFLOAT3(xS, startTextY + letterBottom, startTextZ) },

		// T
		{ pLetterHMesh, XMFLOAT3(xT1, startTextY + letterTop, startTextZ) },
		{ pLetterVMesh, XMFLOAT3(xT1, startTextY, startTextZ) },

		// A
		{ pLetterHMesh, XMFLOAT3(xA, startTextY + letterTop, startTextZ) },
		{ pLetterHMesh, XMFLOAT3(xA, startTextY + letterMid, startTextZ) },
		{ pLetterVMesh, XMFLOAT3(xA + letterLeft, startTextY, startTextZ) },
		{ pLetterVMesh, XMFLOAT3(xA + letterRight, startTextY, startTextZ) },

		// R
		{ pLetterHMesh, XMFLOAT3(xR, startTextY + letterTop, startTextZ) },
		{ pLetterHMesh, XMFLOAT3(xR, startTextY + letterMid, startTextZ) },
		{ pLetterVMesh, XMFLOAT3(xR + letterLeft, startTextY, startTextZ) },
		{ pLetterVMesh, XMFLOAT3(xR + letterRight, startTextY + 7.0f, startTextZ) },
		{ pLetterVMesh, XMFLOAT3(xR + letterRight, startTextY - 8.0f, startTextZ) },

		// T
		{ pLetterHMesh, XMFLOAT3(xT2, startTextY + letterTop, startTextZ) },
		{ pLetterVMesh, XMFLOAT3(xT2, startTextY, startTextZ) }
	};

	// 구조체 배열을 실제 CGameObject로 만든 뒤, 시작화면 오브젝트 배열에 넣음
	int nStartObjectCount = sizeof(startObjects) / sizeof(startObjects[0]);
	for (int i = 0; i < nStartObjectCount; i++)
	{
		CGameObject* pObject = new CGameObject();
		pObject->SetMesh(startObjects[i].pMesh);
		pObject->SetPosition(startObjects[i].xmf3Position);
		m_vStartStageObjects.push_back(pObject);
	}

	// 선택된 스테이지 테두리만 Render()에서 그림
	float borderZ = 328.0f;
	float borderHalfWidth = 58.0f;
	float borderHalfHeight = 40.0f;
	XMFLOAT3 stage1Center = XMFLOAT3(-50.0f, buttonY + 20.0f, borderZ);
	XMFLOAT3 stage2Center = XMFLOAT3(350.0f, buttonY + 20.0f, borderZ);

	struct SSelectionObjectInfo
	{
		std::vector<CGameObject*>* pvObjects;
		CMesh* pMesh;
		XMFLOAT3 xmf3Position;
	};

	SSelectionObjectInfo selectionObjects[] =
	{
		// 1스테이지 선택 테두리: 위, 아래, 왼쪽, 오른쪽
		{ &m_vStage1SelectObjects, pBorderHMesh, XMFLOAT3(stage1Center.x, stage1Center.y + borderHalfHeight, borderZ) },
		{ &m_vStage1SelectObjects, pBorderHMesh, XMFLOAT3(stage1Center.x, stage1Center.y - borderHalfHeight, borderZ) },
		{ &m_vStage1SelectObjects, pBorderVMesh, XMFLOAT3(stage1Center.x - borderHalfWidth, stage1Center.y, borderZ) },
		{ &m_vStage1SelectObjects, pBorderVMesh, XMFLOAT3(stage1Center.x + borderHalfWidth, stage1Center.y, borderZ) },

		// 2스테이지 선택 테두리: 위, 아래, 왼쪽, 오른쪽
		{ &m_vStage2SelectObjects, pBorderHMesh, XMFLOAT3(stage2Center.x, stage2Center.y + borderHalfHeight, borderZ) },
		{ &m_vStage2SelectObjects, pBorderHMesh, XMFLOAT3(stage2Center.x, stage2Center.y - borderHalfHeight, borderZ) },
		{ &m_vStage2SelectObjects, pBorderVMesh, XMFLOAT3(stage2Center.x - borderHalfWidth, stage2Center.y, borderZ) },
		{ &m_vStage2SelectObjects, pBorderVMesh, XMFLOAT3(stage2Center.x + borderHalfWidth, stage2Center.y, borderZ) }
	};

	int nSelectionObjectCount = sizeof(selectionObjects) / sizeof(selectionObjects[0]);
	for (int i = 0; i < nSelectionObjectCount; i++)
	{
		CGameObject* pObject = new CGameObject();
		pObject->SetMesh(selectionObjects[i].pMesh);
		pObject->SetPosition(selectionObjects[i].xmf3Position);
		selectionObjects[i].pvObjects->push_back(pObject);
	}
}
void CObjectsShader::SetResultObjectPosition(CPlayer* pPlayer)
{
	if (!pPlayer) return;

	XMFLOAT3 pos = pPlayer->GetPosition();
	XMFLOAT3 look = pPlayer->GetLookVector();

	XMFLOAT3 resultPos = XMFLOAT3(
		pos.x + look.x * 300.0f,
		pos.y + 20.0f,
		pos.z + look.z * 300.0f
	);

	for (CGameObject* pObject : m_vGameOverObjects)
	{
		if (pObject) pObject->SetPosition(resultPos);
	}

	for (CGameObject* pObject : m_vGameClearObjects)
	{
		if (pObject) pObject->SetPosition(resultPos);
	}
}

void CObjectsShader::BuildCrossHair(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	CCubeMeshDiffused* pHMesh = new CCubeMeshDiffused(
		pd3dDevice,
		pd3dCommandList,
		20.0f, 2.0f, 2.0f,
		XMFLOAT4(1.0f, 0.8f, 0.9f, 1.0f)
	);

	CCubeMeshDiffused* pVMesh = new CCubeMeshDiffused(
		pd3dDevice,
		pd3dCommandList,
		2.0f, 20.0f, 2.0f,
		XMFLOAT4(1.0f, 0.8f, 0.9f, 1.0f)
	);

	m_pCrossHairH = new CGameObject();
	m_pCrossHairH->SetMesh(pHMesh);

	m_pCrossHairV = new CGameObject();
	m_pCrossHairV->SetMesh(pVMesh);
}

// 조준점 위치 업데이트
void CObjectsShader::UpdateCrossHair(CCamera* pCamera)
{
	if (!pCamera || !m_pCrossHairH || !m_pCrossHairV) return;

	XMFLOAT3 camPos = pCamera->GetPosition();
	XMFLOAT3 camLook = pCamera->GetLookVector();

	float distance = 120.0f;

	XMFLOAT3 crossPos = XMFLOAT3(
		camPos.x + camLook.x * distance,
		camPos.y + camLook.y * distance,
		camPos.z + camLook.z * distance
	);

	m_pCrossHairH->SetPosition(crossPos);
	m_pCrossHairV->SetPosition(crossPos);

	m_pCrossHairH->SetLookDirection(camLook);
	m_pCrossHairV->SetLookDirection(camLook);
}