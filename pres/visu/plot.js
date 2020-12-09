let DENSITY = document.getElementById('density');

if (window.fetch) {
  fetch('visu/visu.csv')
    .then(function(response) {
      return response.blob();
    })
    .then(function(blob) {
      return blob.text();
    })
    .then(function(text) {
      if (text.length > 0) updateDensityPlot(text);
    })
    .catch(e => console.error(e));
}

function updateDensityPlot(csvData) {
  if (!csvData) return;
  csvData = csvData.split("\n");
  console.log(csvData);

  let X = [],
    Z = [],
    dens = [];

  let i = 0;
  while (i < csvData.length && csvData[i].trim() != ";") {
    X.push(Number(csvData[i]));
    i++;
  }

  i++;
  while (i < csvData.length && csvData[i].trim() != ";") {
    Z.push(Number(csvData[i]));
    i++;
  }

  i++;
  for (; i < csvData.length; i++) {
    dens.push(csvData[i].split(",").map(el => Number(el)));
  }

  let data = [{
    x: Z,
    y: X,
    z: dens,
    type: 'heatmap',
    // Inferno
    colorscale: [
      [0.0, '#000000'],
      [0.1, '#160B38'],
      [0.3, '#6B166E'],
      [0.5, '#BD3853'],
      [0.7, '#F3781A'],
      [0.9, '#F5D949'],
      [1.0, '#FCFDA4']
    ],
    colorbar: {
      ypad: 0,
      xpad: 0,
      thickness: 20,
      ticks: '',
      showticklabels: true
    },
    zsmooth: 'none'
  }];

  let layout = {
    title: 'Nuclear local density in the (x, z) plane',
    height: 430,
    width: 635,
    xaxis: {
      title: 'Z-axis'
    },
    yaxis: {
      title: 'X-axis'
    },
  };

  Plotly.newPlot(DENSITY, data, layout);
}