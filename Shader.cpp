// Shader.cpp
#include "stdafx.h"
#include "Shader.h"
#include "Player.h"

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
	// 도착 지점 메쉬 생성
	CCubeMeshDiffused* pGoalMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f, 
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));

	float floorThickness = 20.0f;
	float floorStepHeight = 20.0f;

	// 바닥 메쉬 생성
	CCubeMeshDiffused* pFloorMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 
		150.0f, floorThickness, 150.0f, XMFLOAT4(1.0f, 0.8f, 0.6f, 1.0f));

	BuildMazeMap();   // 미로 생성
	BuildFloorMap();  // 바닥 생성
	BuildEnemies(pd3dDevice, pd3dCommandList); // 적 생성

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


	// 도착 지점 큐브
	CGameObject* pGoal = new CGameObject();
	pGoal->SetMesh(pGoalMesh);

	float goalY = m_Floor[9][9] * floorStepHeight;

	pGoal->SetPosition(fxPitch * 9, goalY + 6.0f, fzPitch * 9);

	m_ppObjects[i++] = pGoal;

	m_nObjects = i;

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
	for (CEnemyObject* pEnemy : m_vEnemies)
	{
		delete pEnemy;
	}
	m_vEnemies.clear();
}

void CObjectsShader::AnimateObjects(float fTimeElapsed, CPlayer* pPlayer)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}

	if (pPlayer)
	{
		XMFLOAT3 playerPos = pPlayer->GetPosition();

		for (CEnemyObject* pEnemy : m_vEnemies)
		{
			if (pEnemy)
			{
				pEnemy->MoveToPlayer(playerPos, fTimeElapsed);
			}
		}
	}
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

void CObjectsShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
	for (CEnemyObject* pEnemy : m_vEnemies)
	{
		if (pEnemy) pEnemy->Render(pd3dCommandList, pCamera);
	}
}

// 미로 맵 만들기	, 0이면 빈 공간, 1이면 벽
void CObjectsShader::BuildMazeMap()
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

// 충돌 검사 함수
bool CObjectsShader::CheckObjectCollision(CPlayer* pPlayer)
{
	if (!pPlayer) return false;
	if (!pPlayer->HasBoundingBox()) return false;

	BoundingBox playerBox = pPlayer->GetBoundingBox();

	for (int i = 0; i < m_nObjects; i++)
	{
		if (!m_ppObjects[i]) continue;
		if (!m_ppObjects[i]->HasBoundingBox()) continue;

		BoundingBox objectBox = m_ppObjects[i]->GetBoundingBox();

		if (playerBox.Intersects(objectBox))
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
	CCubeMeshDiffused* pEnemyMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		40.0f, 60.0f, 40.0f, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
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
		pEnemy->SetBoundingBox(pos, XMFLOAT3(20.0f, 30.0f, 20.0f));
		pEnemy->SetMoveSpeed(60.0f);

		m_vEnemies.push_back(pEnemy);
	}
}