// �t���O�����g�V�F�[�_�[
#version 330 core

in vec3 FragPos;

uniform vec3 lightPos;   // �X�|�b�g���C�g�̈ʒu
uniform vec3 lightDir;   // �X�|�b�g���C�g�̌���
uniform vec3 viewPos;    // �J�����̈ʒu

out vec4 FragColor;

void main() {
    // �X�|�b�g���C�g�̉e���͈͓����ǂ������v�Z
    vec3 lightDirNorm = normalize(lightDir);
    vec3 fragToLight = normalize(lightPos - FragPos);
    float spotFactor = dot(lightDirNorm, -fragToLight);
    float spotlightEffect = smoothstep(0.9, 1.0, spotFactor);

    // �Ԃ��F���g���ĕ`��
    FragColor = vec4(1.0, 0.0, 0.0, 1.0) * spotlightEffect;
}