#pragma once

#include <format>
#include <string>

namespace rz_webserver {

inline std::string htmlHeader()
{
    const std::string html = R"(<!DOCTYPE html>
<html lang="en" data-theme="dark">
  <head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <meta name="robots" content="index,follow" />
        
    <title>RZheng: landing page</title>
  </head>
  <body>
)";
    return html;
}

inline std::string htmlEnd()
{
    const std::string html = R"(
  </body>
</html>
)";
    return html;
}

inline std::string getForm()
{
    const std::string html = R"(
<form id="formElem">
  <input type="file" name="image_file" accept="image/*">
  <input type="file" name="text_file" accept="text/*">
  <input type="submit">
</form>
<script>
  formElem.onsubmit = async (e) => {
    e.preventDefault();
    let res = await fetch('/post', {
      method: 'POST',
      body: new FormData(formElem)
    });
    console.log(await res.text());
  };
</script>
)";

    std::string ret = std::format("{}{}{}", htmlHeader(), html, htmlEnd());
    return ret;
}

} // namespace rz_webserver
