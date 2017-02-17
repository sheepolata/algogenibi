/**
 * Created by raphael on 15/02/2017.
 */

var drawPlot = function (data) {

    svg = d3.select("body").append("svg")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom);


    g = svg.append("g")
        .attr("transform", "translate(" + ((width + margin.left + margin.right)/2 - w/2) + "," + ((height + margin.top + margin.bottom)/2 - w/2) + ")");

    var x = d3.scaleLinear()
        .range([margin.left, width + margin.left]);

    var y = d3.scaleLinear()
        .range([height + margin.top, margin.top]);

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
        d3.min(data, function(d) { return d.rho_c; }),
        d3.max(data, function(d) { return d.rho_c; })
    ]);

    svg.append("g")
        .attr("class", "x axis")
        .attr("transform", "translate(0," + (height + margin.top)  + ")")
        .call(xAxis);

    svg.append("g")
        .attr("class", "y axis")
        .attr("transform", "translate(" + margin.left + ", 0)")
        .call(yAxis);

    var rho_c = d3.line()
        .x(function(d, i) { return x(i); })
        .y(function(d) { return y(d.rho_c); });


    svg.append("path")
        .data(data)
        .attr("id", "rho_c")
        .attr("class", "rho_c")
        .attr("d", rho_c(data))
        .style("stroke", "blue")
        .style("fill", "none");

};


