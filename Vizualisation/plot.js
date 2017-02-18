/**
 * Created by raphael on 15/02/2017.
 */

var x;
var y;

//var rho_c;
var p;
var i;

var x_extension = 300;

var drawPlot = function (data) {

    svg = d3.select("body").append("svg")
        .attr("width", width + margin.left + margin.right + x_extension)
        .attr("height", height + margin.top + margin.bottom);


    g = svg.append("g")
        .attr("transform", "translate(" + ((width + margin.left + margin.right) / 2 - w / 2) + "," + ((height + margin.top + margin.bottom) / 2 - w / 2) + ")");

    x = d3.scaleLinear()
        .range([margin.left, width + margin.left + x_extension]);
    y = d3.scaleLinear()
        .range([height + margin.top, 1]);

    /*rho_c  = d3.line()
     .x(function(d, i) { return x(i); })
     .y(function(d) { return y(d.rho_c); });*/

    p = d3.line()
        .x(function (d, i) {
            return x(i);
        })
        .y(function (d) {
            return y(d.p);
        });

    i = d3.line()
        .x(function (d, i) {
            return x(i);
        })
        .y(function (d) {
            return y(d.i);
        });


    var xAxis = d3.axisBottom(x)
        .ticks(5)
        .tickSizeInner(1)
        .tickSizeOuter(0);

    var yAxis = d3.axisLeft(y)
        .ticks(10)
        .tickSizeInner(1)
        .tickSizeOuter(0);


    x.domain([0, data.length]);

    y.domain([
        Math.min(d3.min(data, function (d) {
            return d.p;
        }), d3.min(data, function (d) {
            return d.i;
        })),
        Math.max(d3.max(data, function (d) {
            return d.p;
        }), d3.max(data, function (d) {
            return d.i;
        }))
    ]);

    svg.append("g")
        .attr("class", "x axis")
        .attr("transform", "translate(0," + (height + margin.top) + ")")
        .call(xAxis);

    svg.append("g")
        .attr("class", "y axis")
        .attr("transform", "translate(" + margin.left + ", 0)")
        .call(yAxis);


    g.append("text")
        .attr("id", "redLegend")
        .attr("x", width / 2)
        .attr("y", -30)
        .attr("dy", "0.1em")
        .style("fill", "red")
        .style("text-anchor", "middle")
        .text("depth");

    g.append("text")
        .attr("id", "greenLegend")
        .attr("x", width / 2)
        .attr("y", -10)
        .attr("dy", "0.1em")
        .style("fill", "green")
        .style("text-anchor", "middle")
        .text("iris size");


    /*svg.append("path")
     .data(data)
     .attr("id", "rho_c")
     .attr("class", "rho_c")
     .attr("d", rho_c(data))
     .style("stroke", "blue")
     .attr("stroke-width", 1.5)
     .attr("shape-rendering", "geometricPrecision")
     .style("fill", "none");*/

    svg.append("path")
        .data(data)
        .attr("id", "p")
        .attr("class", "p")
        .attr("d", "")
        .style("stroke", "red")
        .attr("stroke-width", 1)
        .attr("shape-rendering", "geometricPrecision")
        .style("fill", "none");

    svg.append("path")
        .data(data)
        .attr("id", "i")
        .attr("class", "i")
        .attr("d", "")
        .style("stroke", "green")
        .attr("stroke-width", 1)
        .attr("shape-rendering", "geometricPrecision")
        .style("fill", "none");

};

function updatePlot(data) {

    /*d3.select("#rho_c")
     .attr("d", rho_c(data));*/

    d3.select("#p")
        .attr("d", p(data));

    d3.select("#i")
        .attr("d", i(data));
}


