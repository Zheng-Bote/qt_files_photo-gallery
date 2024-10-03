window.onload = start;

function start() {
  const url = window.location;
  const origin = "{{ site.page_url }}/";
  const path = url.pathname;
  let a_arr = path.split("/");
  let html = "false";

  const arr = a_arr.filter(rmEmpty);

  if (path.endsWith(".html")) {
    arr.length = arr.length - 1;
  }

  const bread = document.getElementById("bread");

  bread.innerHTML = `<li><a href="${origin}">Main</a>`;

  if (a_arr.length === 0) {
    return;
  }

  const uri_arr = [];
  for (let i = 1; i < arr.length; i++) {
    uri_arr.push(arr[i]);
    let text = origin;
    text += uri_arr.join("/");

    //bread.innerHTML += `<li><a href="${text}">${arr[i]}</a></li>`;

    if (i === arr.length - 1) {
      if (path.endsWith(".html")) {
        bread.innerHTML += `<li><a href="${text}">${arr[i]}</a></li>`;
      } else {
        bread.innerHTML += `<li>${arr[i]}</li>`;
      }
    } else {
      bread.innerHTML += `<li><a href="${text}">${arr[i]}</a></li>`;
    }
  }

  function rmEmpty(item) {
    if (item.length > 0) {
      return item;
    }
  }
  