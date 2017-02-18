/**
 * Created by raphael on 12/02/2017.
 */

var _w = 1.5; // in cm
var metric_scale = 100;
var w = _w * metric_scale;

var svg;
var g;
var epsilon = 0.002;

var initEye = function () {
    // Set graphic elements
    svg = d3.select("body").append("svg")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom);

    g = svg.append("g")
        .attr("transform", "translate(" + ((width + margin.left + margin.right) / 2 - w / 2) + "," + ((height + margin.top + margin.bottom) / 2 - w / 2) + ")");

    // Trace reference axis
    var vertical = svg.append("line")
        .attr("id", "vertical_axis")
        .attr("x1", (width + margin.left + margin.right) / 2)
        .attr("y1", 0)
        .attr("x2", (width + margin.left + margin.right) / 2)
        .attr("y2", height + margin.top + margin.bottom)
        .style("stroke-dasharray", ("3, 3"))
        .style("stroke", "black");

    var horizontal = svg.append("line")
        .attr("id", "horizontal_axis")
        .attr("x1", 0)
        .attr("y1", (height + margin.top + margin.bottom) / 2)
        .attr("x2", width + margin.left + margin.right)
        .attr("y2", (height + margin.top + margin.bottom) / 2)
        .style("stroke-dasharray", ("3, 3"))
        .style("stroke", "black");


    // center point
    /*var origin = g.append("circle")
     .attr("id", "origin")
     .attr("cx", 0)
     .attr("cy", 0)
     .attr("r", 3)
     .style("fill", "blue")
     .attr("transform", "translate("+(w/2)+","+(w/2)+")");*/
};

var computePoint = function (data) {
    var points = {};

    var _a = data.a; // in cm
    var _i = data.i; // in cm
    var _rho_c = data.rho_c; // in cm
    var _phi_1 = data.phi_1; // in rad

    // variables for the visualization

    var rho_c = _rho_c * metric_scale;

    var i = _i * metric_scale;
    var a = _a * metric_scale;

    var phi_1 = _phi_1;


    var x_A = -w / 2;
    var y_A;

    var x_B = w / 2;
    var y_B;


    var x_E = -a / 2;
    var y_E;

    var x_F = a / 2;
    var y_F;

    var semi_depth = 0;

    if (Math.abs(rho_c - w / 2) < epsilon) {
        y_A = 0;
        var x_C = -1 * Math.cos(phi_1) * rho_c;
        var y_C = -1 * Math.sin(phi_1) * rho_c;

        var x_D = Math.cos(phi_1) * rho_c;
        var y_D = y_C;

        y_E = y_C;
        y_F = y_C;

        points.x_C = x_C;
        points.y_C = y_C;
        points.x_D = x_D;
        points.y_D = y_D;

    } else if (rho_c > w / 2) {
        var phi_0 = Math.acos((w / 2) / rho_c);
        semi_depth = Math.sqrt(rho_c * rho_c - (w / 2) * (w / 2));

        y_A = 0;
        y_E = y_A;
        y_F = y_A;

        points.phi_0 = phi_0;

    }

    points.semi_depth = semi_depth;

    y_B = y_A;

    points.rho_c = rho_c;
    points.phi_1 = phi_1;
    points.i = i;
    points.a = a;

    points.x_A = x_A;
    points.y_A = y_A;
    points.x_B = x_B;
    points.y_B = y_B;
    points.x_E = x_E;
    points.y_E = y_E;
    points.x_F = x_F;
    points.y_F = y_F;

    return points;

};

var cavity = function (points) {
    return d3.arc()
        .innerRadius(points.rho_c - 1)
        .outerRadius(points.rho_c + 1)
        .startAngle(function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return Math.PI / 2 - points.phi_1;
            } else if (points.rho_c > w / 2) {
                return Math.PI / 2 + points.phi_0;
            }
        })
        .endAngle(function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return 3 * Math.PI / 2 + points.phi_1;
            } else if (points.rho_c > w / 2) {
                return 3 * Math.PI / 2 - points.phi_0;
            }
        });
};

// draw the eye representation
var drawEye = function (data) {
    //rho_c	    i	        phi_1	    n0	        p	        a	        r1	        teta
    //console.log(data);

    var points = computePoint(data);

    // point of view
    g.append("circle")
        .attr("id", "point_of_view")
        .attr("cx", 0)
        .attr("cy", 0)
        .attr("r", 3)
        .style("fill", "red")
        .attr("transform", "translate(" + (w / 2) + "," + (w / 2 - points.semi_depth) + ")");

    // left iris part
    g.append("line")
        .attr("id", "left_iris")
        .attr("x1", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.x_C;
            } else if (points.rho_c > w / 2) {
                return points.x_A;
            }

        })
        .attr("y1", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.y_C;
            } else if (points.rho_c > w / 2) {
                return points.y_A;
            }

        })
        .attr("x2", points.x_E)
        .attr("y2", points.y_E)
        .style("stroke", "black")
        .style("stroke-width", 2)
        .attr("transform", "translate(" + (w / 2) + "," + (w / 2) + ")");

    // right iris part
    g.append("line")
        .attr("id", "right_iris")
        .attr("x1", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.x_D;
            } else if (points.rho_c > w / 2) {
                return points.x_B;
            }

        })
        .attr("y1", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.y_D;
            } else if (points.rho_c > w / 2) {
                return points.y_B;
            }

        })
        .attr("x2", points.x_F)
        .attr("y2", points.y_F)
        .style("stroke", "black")
        .style("stroke-width", 2)
        .attr("transform", "translate(" + (w / 2) + "," + (w / 2) + ")");


    // arc cavity
    var arc = cavity(points);

    g.append("path")
        .attr("id", "cavity")
        .attr("class", "arc")
        .attr("d", arc)
        .attr("transform", "translate(" + (w / 2) + "," + (w / 2 - points.semi_depth) + ")");


    // To smooth the edge
    g.append("circle")
        .attr("id", "left_edge")
        .attr("cx", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.x_C;
            } else if (points.rho_c > w / 2) {
                return points.x_A;
            }
        })
        .attr("cy", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.y_C;
            } else if (points.rho_c > w / 2) {
                return points.y_A;
            }
        })
        .attr("r", 1)
        .style("fill", "black")
        .attr("transform", "translate(" + (w / 2) + "," + (w / 2) + ")");

    g.append("circle")
        .attr("id", "right_edge")
        .attr("cx", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.x_D;
            } else if (points.rho_c > w / 2) {
                return points.x_B;
            }
        })
        .attr("cy", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.y_D;
            } else if (points.rho_c > w / 2) {
                return points.y_B;
            }
        })
        .attr("r", 1)
        .style("fill", "black")
        .attr("transform", "translate(" + (w / 2) + "," + (w / 2) + ")");
};

var updateEye = function (data) {

    var points = computePoint(data);

    d3.select("#point_of_view")
        .attr("transform", "translate(" + (w / 2) + "," + (w / 2 - points.semi_depth) + ")");

    d3.select("#left_iris")
        .attr("x1", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.x_C;
            } else if (points.rho_c > w / 2) {
                return points.x_A;
            }

        })
        .attr("y1", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.y_C;
            } else if (points.rho_c > w / 2) {
                return points.y_A;
            }

        })
        .attr("x2", points.x_E)
        .attr("y2", points.y_E);


    d3.select("#right_iris")
        .attr("x1", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.x_D;
            } else if (points.rho_c > w / 2) {
                return points.x_B;
            }

        })
        .attr("y1", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.y_D;
            } else if (points.rho_c > w / 2) {
                return points.y_B;
            }

        })
        .attr("x2", points.x_F)
        .attr("y2", points.y_F);

    d3.select("#left_edge")
        .attr("cx", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.x_C;
            } else if (points.rho_c > w / 2) {
                return points.x_A;
            }
        })
        .attr("cy", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.y_C;
            } else if (points.rho_c > w / 2) {
                return points.y_A;
            }
        });

    d3.select("#right_edge")
        .attr("cx", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.x_D;
            } else if (points.rho_c > w / 2) {
                return points.x_B;
            }
        })
        .attr("cy", function () {
            if (Math.abs(points.rho_c - w / 2) < epsilon) {
                return points.y_D;
            } else if (points.rho_c > w / 2) {
                return points.y_B;
            }
        });

    var arc = cavity(points);

    d3.select("#cavity")
        .attr("d", arc)
        .attr("transform", "translate(" + (w / 2) + "," + (w / 2 - points.semi_depth) + ")");

};
