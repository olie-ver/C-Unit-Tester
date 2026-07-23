#pragma once

#ifndef RENDER_HELP_H
#define RENDER_HELP_H

#include <string>

namespace internal {
    namespace Renderer {
        namespace Helpers {
            static inline std::string escapeJson(const std::string& input) {
                std::string output;
                output.reserve(input.size());

                for (char c : input) {
                    switch (c) {
                        case '\"':
                            output += "\\\"";
                            break;

                        case '\\':
                            output += "\\\\";
                            break;

                        case '\b':
                            output += "\\b";
                            break;

                        case '\f':
                            output += "\\f";
                            break;

                        case '\n':
                            output += "\\n";
                            break;

                        case '\r':
                            output += "\\r";
                            break;

                        case '\t':
                            output += "\\t";
                            break;

                        default:
                            output += c;
                            break;
                    }
                }

                return output;
            }

            static inline std::string escapeXml(const std::string& input) {
                std::string output;
                output.reserve(input.size());

                for (char c : input) {
                    switch (c) {
                        case '&':
                            output += "&amp;";
                            break;

                        case '<':
                            output += "&lt;";
                            break;

                        case '>':
                            output += "&gt;";
                            break;

                        case '\"':
                            output += "&quot;";
                            break;

                        case '\'':
                            output += "&apos;";
                            break;

                        default:
                            output += c;
                            break;
                    }
                }

                return output;
            }
        }
    }
}

#endif