#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader &shader)
{
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position,
                                glm::vec2 roi, glm::vec2 offset,
                                glm::vec2 size, float rotate,
                                glm::vec3 color)
{
    // prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);

    // Các bước biến hình: scale, rotate, translate
    // nhưng khi tiến hành trong code, thì cần làm ngược lại để thực hiện việc tính toán
    model = glm::translate(model, glm::vec3(position, 0.0f)); // first translate (transformations are: scale happen first, then rotation, and then final translation happens; reverse order
    // Khi load texture, ta đang tính toán mốc tọa độ O(0, 0) tại top-left của texture
    // -> cần move origin về center của image trước khi rotate image
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to the center of the quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move the origin back to the top-left of the quad
    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    // Theo thứ tự nhân ma trận:
    // 1. scale
    // 2. rotate
    // 3. translate
    // Ta thấy có 2 hàm translate xen giữa. Do hiện tại, ta đang định nghĩa gốc 0 tại vị trí top-left của 1 quad
    // -> cần đưa gốc 0 về vị trí tâm của quad (hình vuông) để rotate the quad 1 cách chính xác
    // -> translate sang phải- xuống dưới (0.5f, 0.5f) tương ứng 50% theo 2 chiều (x, y) (trong đó, tại mỗi chiều, coi như quad có độ dài 1.0f)
    // -> sau khi rotate thành công, ta lại đưa gốc O về vị trí top-left của quad.
    // -> sau đó, ta thực hiện translate như bình thường
    this->shader.SetMatrix4("model", model);

    // render texture quad
    this->shader.SetVector3f("spriteColor", color);
    this->shader.SetVector2f("roi", roi);
    this->shader.SetVector2f("offset", offset);

    // Ở ngoài Game.cpp, có dòng định nghĩa dưới đây:
    // ResourceManager::GetShader("sprite").SetInteger("image", 0);
    // dòng code tại Game.cpp định nghĩa Sampler2D tại vị trí GL_TEXTURE0 với tên là image.
    // ta có thể thay đổi giá trị của GL_TEXTURE[xxx] và thay đổi name từ 'image' sang các giá trị khác nhau để thử.
    glActiveTexture(GL_TEXTURE0);

    // Do trong 1 chương trình, ta cần dùng đến rất nhiều sprite khác nhau
    // -> render  liên tục với các texture khác nhau cho mỗi shader.
    // Sau khi active 1 sampler(2D) tại vị trí cần active -> bind texture tại ID cần sử dụng
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // unbind the vertex array by pointing to ID 0
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VAO, VBO;
    // tex
    // 0.0f, 1.0f, top left
    // 1.0f, 0.0f, bot right
    // 0.0f, 0.0f, bot left
    // 
    // 0.0f, 1.0f, top left
    // 1.0f, 1.0f, top right
    // 1.0f, 0.0f, bot right

    // pos    
    //0.0f, 1.0f 
    //1.0f, 0.0f
    //0.0f, 0.0f
    //
    //0.0f, 1.0f
    //1.0f, 1.0f
    //1.0f, 0.0f
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    
    // load cả 4 giá trị float của array vertices vào VAO tại location 0
    // đây chính là lý do vì sao trong file shader:
    // - giá trị vertex truyền vào là vec4(x,y,z,w)
    // - giá trị xy là position của vertex
    // - giá trị zw là giá trị texture coordinate
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // release buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 
}