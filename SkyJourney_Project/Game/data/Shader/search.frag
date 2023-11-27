// フラグメントシェーダー
#version 330 core

in vec3 FragPos;

uniform vec3 lightPos;   // スポットライトの位置
uniform vec3 lightDir;   // スポットライトの向き
uniform vec3 viewPos;    // カメラの位置

out vec4 FragColor;

void main() {
    // スポットライトの影響範囲内かどうかを計算
    vec3 lightDirNorm = normalize(lightDir);
    vec3 fragToLight = normalize(lightPos - FragPos);
    float spotFactor = dot(lightDirNorm, -fragToLight);
    float spotlightEffect = smoothstep(0.9, 1.0, spotFactor);

    // 赤い色を使って描画
    FragColor = vec4(1.0, 0.0, 0.0, 1.0) * spotlightEffect;
}