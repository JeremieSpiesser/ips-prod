let DENSITY = document.getElementById('density');

if (window.fetch) {
  fetch('visu.csv')
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
    colorscale: [ [0.0,'#000000'], [0.1,'#0000FF'], [0.3,'#00FFFF'], [0.5,'#00FF00'], [0.7,'#FFFF00'], [0.9,'#FF0000'], [1.0,'#FFFFFF'] ],
    colorbar: {ypad: 0, xpad: 0, thickness: 20, ticks: '', showticklabels: true},
    zsmooth: 'best'
  }];

  let layout = {
    title: 'Nuclear local density in the (x, z) plane',
    autosize: true,
    xaxis: {title: 'Z-axis'},
    yaxis: {title: 'X-axis'},
  };

  Plotly.newPlot(DENSITY, data, layout);
}
