Chart.defaults.global.responsive = true;
var temperatureChart = {};
temperatureChart.options = {
    animation: true,
    animationSteps: 20,
    pointDot: true,
    datasetFill: false,
    scaleOverride: true, //是否用硬编码重写y轴网格线
    scaleSteps: 5, //y轴刻度的个数
    scaleStepWidth: 8, //y轴每个刻度的宽度
    scaleStartValue: 0, //y轴的起始值

    scaleShowGridLines: true,
    scaleGridLineColor: "rgba(255,255,255,.03)",
    scaleGridLineWidth: 1,
    scaleShowHorizontalLines: true,
    scaleShowVerticalLines: false,
    scaleLabel:"<%=value%> ℃"
};
temperatureChart.data = {
    labels: ["", "", "", "", "", "", "", "", "", "","", ""],
    datasets: [
        {
            label: "My chart",
            fillColor: "RGBA(42, 159, 214, 0.20)",
            strokeColor: "RGBA(42, 159, 214, 1.00)",
            pointColor: "RGBA(42, 159, 214, 1.00)",
            pointStrokeColor: "#fff",
            pointHighlightFill: "#fff",
            pointHighlightStroke: "rgba(151,187,205,1)",
            data: [18, 38, 40, 19, 26, 17, 40, 20, 11, 19,18, 38]
        }
    ]
};

var myTemperatureChart = new Chart($("#temperature").get(0).getContext("2d")).Line(temperatureChart.data, temperatureChart.options);


var humidityChart = {};
humidityChart.options = {
    animation: true,
    animationSteps: 20,
    pointDot: true,
    datasetFill: false,
    scaleOverride: true, //是否用硬编码重写y轴网格线
    scaleSteps: 5, //y轴刻度的个数
    scaleStepWidth: 20, //y轴每个刻度的宽度
    scaleStartValue: 0, //y轴的起始值

    scaleShowGridLines: true,
    scaleGridLineColor: "rgba(255,255,255,.03)",
    scaleGridLineWidth: 1,
    scaleShowHorizontalLines: true,
    scaleShowVerticalLines: false,
    scaleLabel: "<%=value%> %"
};
humidityChart.data = {
    labels: ["", "", "", "", "", "", "", "", "", "","", ""],
    datasets: [
        {
            label: "My chart",
            fillColor: "RGBA(204, 0, 0, 0.20)",
            strokeColor: "RGBA(204, 0, 0, 1.00)",
            pointColor: "RGBA(204, 0, 0, 1.00)",
            pointStrokeColor: "#fff",
            pointHighlightFill: "#fff",
            pointHighlightStroke: "rgba(151,187,205,1)",
            data: [28, 48, 40, 19, 86, 27, 90, 48, 40, 19,28, 48]
        }
    ]
};

var myhumidityChart = new Chart($("#humidity").get(0).getContext("2d")).Line(humidityChart.data, humidityChart.options);

function updataChart(data) {

    myTemperatureChart.removeData();
    myTemperatureChart.addData([data.temperature], "");
    myhumidityChart.removeData();
    myhumidityChart.addData([data.humidity], "");
}





function toggleLED(status) {
    $.post('api/led', {
        led: status
    }, function (data) {
        console.log(data);
    });
}

function sentColor(color) {
    $.post('api/rgb', {
        color: color,
    }, function (data) {
        console.log(data);
    });
}


var websocket;

function doSend(message) {
    websocket.send(message);
}

function doDisconnect() {
    websocket.close();
}

function startWebSocket() {
    var wsUri = "ws://" + location.host + "/";
    websocket = new WebSocket(wsUri);
    websocket.onopen = function (evt) {
        console.log("websocket open");
    };
    websocket.onclose = function (evt) {
        console.log("websocket close");
    };

    websocket.onmessage = function (evt) {
        updataChart(JSON.parse(evt.data));
    };
    websocket.onerror = function (evt) {
        console.log("websocket onerror");
    };
}

$(document).ready(function () {
    startWebSocket();
});
