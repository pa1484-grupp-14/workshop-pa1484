

/*
    https://opendata-download-metobs.smhi.se/api/version/latest/parameter/{option}.json    //// get alla the sations
    station > name   /// stationsnamn
    station > key    /// key för station

    https://opendata-download-metobs.smhi.se/api/version/{version}/parameter/{option}/station/{station}/period/{period}/data.json    /////  ger all data givet det som skickats
     "value": [{
      "date": 1650949200000,
      "value": "-3.2",
      "quality": "G"]},
*/

//StationsName = stations name attribute not key, typeOfData = parameter

baseURLHistorical = "https://opendata-download-metobs.smhi.se/api/version/latest/parameter";
baseURLForecast = "https://opendata-download-metfcst.smhi.se/api/category/snow1g/version/1/geotype/point/lon";


getStationsArray = async(parameter) =>
{
    let promise = new Promise(resolve =>
    {
        fetch(`${baseURLHistorical}/${parameter}.json`)
        .then(response => response.json())
        .then(response =>  {
            resolve(response["station"]);
        });
    });
    value = await promise;
    return value;
}

getStationFromArray = (array, stationName) => {
    counter = 0;
    while(counter != array.length)
    {
        let theName = array[counter]["name"];
        if(theName == stationName)
        {
            return array[counter];
        }
        counter++;
    }
}


//("Abisko Aut", 1, "latest-months", 2)
getHistoricalData = async(key, parameter) => {
    let promise = new Promise(resolve =>
    {
        let data = [];
        let valueToAdd = 0;
        let counter = 0;
        fetch(`${baseURLHistorical}/${parameter}/station/${key}/period/latest-months/data.json`)
        .then(response => response.json())
        .then(response =>  {
            let dataValues = response["value"];
            let dateCompare = new Date(dataValues[0]["date"]);
            let cond = dataValues[0]["date"];
            if(cond != undefined)
            {
                for(i = 0; i < dataValues.length; i++)
                {
                    let date = new Date(dataValues[i]["date"]);
                    if(date.getDate() == dateCompare.getDate())
                    {
                        counter++;
                        valueToAdd += parseFloat(dataValues[i]["value"]); 
                    } 
                    else {
                        valueToAdd = (valueToAdd / counter).toPrecision(2);
                        let millis = dateCompare.getTime();
                        data.push({"date": millis, "value": valueToAdd});
                        counter = 0;
                        valueToAdd = 0;
                        dateCompare = new Date(dataValues[i]["date"]);
                    }
                }
            }
            else
            {
                for(i = 0; i < dataValues.length; i++)
                {
                    let date = new Date(dataValues[i]["from"]);
                    let millis = date.getTime();
                    valueToAdd += parseFloat(dataValues[i]["value"]); 
                    data.push({"From": millis, "value": valueToAdd});
                }
            }
            resolve(data); 
        })
        .catch(()=>{
            console.error("option not available for station");
        })
    });
    return await promise;
}

getForecastNext7Days = async(stationObj) =>{
    longitude = stationObj["longitude"];
    latitude = stationObj["latitude"];
    let data = [];
    let promise = new Promise(resolve =>
    {
        fetch(`${baseURLForecast}/${longitude}/lat/${latitude}/data.json`)
        .then(response => response.json())
        .then(response =>  {
            let dateNow = new Date();
            let nrOfDaysAdded = 0;
            let timeSeries = response["timeSeries"];
            let counter = 0;
            while(nrOfDaysAdded != 7 && counter != timeSeries.length) 
            {
                let entryTime = new Date (timeSeries[counter]["time"]);
                if(dateNow.getDate() != entryTime.getDate())
                {
                    if(entryTime.getUTCHours() == 12)
                    {
                        data.push(timeSeries[counter]);
                        nrOfDaysAdded++;
                    }
                }
                counter++;
            }
            resolve(data);
        });
    });
    value = await promise;
    return value;
    
};


//Example how to Use functions down bellow
window.addEventListener("load", async()=>{
    let array = await getStationsArray(1);
    let station = getStationFromArray(array,"Abisko Aut");
    let dataHistorical = await getHistoricalData(station["key"], 1); 
    let dataForecast =  await getForecastNext7Days(station);

    console.log(array);
    console.log(station);
    console.log(dataHistorical);
    console.log(dataForecast);
})