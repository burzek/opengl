#ifndef D02987D6_D56F_4164_A862_7C92FE130C52
#define D02987D6_D56F_4164_A862_7C92FE130C52

#include <ostream>

enum class ShaderType {
    vertex,
    fragment
};

std::ostream& operator<<(std::ostream& os, const ShaderType shader_type) {
  switch(shader_type) {
    case ShaderType::vertex:
        os << "vertex";
        break;
    case ShaderType::fragment:
        os << "fragment";
        break;
    default:
        os << "UNKNOWN SHADER TYPE ";
        break;
    break;
  }
  return os;
};

#endif /* D02987D6_D56F_4164_A862_7C92FE130C52 */
