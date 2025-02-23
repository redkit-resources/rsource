// 8x8 grid of triangles, each a uniform color.
// Can draw fewer instances, will fill grid left-to-right, top-to-bottom (reading order)
cbuffer globalvs
{
    float4 colors[64];
};

struct PSInput
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};

PSInput vs_main( uint vertexId : SV_VertexID, uint instanceId : SV_InstanceID )
{
	PSInput o;
	float2 verts[3] = 
    {
        { float2( -0.1f,  0.1f ) }, 
		{ float2(  0.0f, -0.1f ) },
        { float2(  0.1f,  0.1f ) },
    };

	float2 gridPos = float2( instanceId % 8, instanceId / 8 );
	float2 instancePos = float2( gridPos.x / 8.0f, 1.0f - gridPos.y / 8.0f ) * 2.0f - 1.0f;
	float2 p = verts[ vertexId ] + instancePos + float2( 0.1f, -0.1f );

	o.pos = float4( p, 0, 1);
	o.col = colors[instanceId];

	return o;
}

float4 ps_main(PSInput i) : SV_TARGET
{
	return i.col;
}
