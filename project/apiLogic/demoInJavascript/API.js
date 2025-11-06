

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
getStationInfo = async(stationName, typeOfData) => {
    let promise = new Promise(resolve =>
    {
        fetch(`https://opendata-download-metobs.smhi.se/api/version/latest/parameter/${typeOfData}.json`)
        .then(response => response.json())
        .then(response =>  {
            counter = 0;
            condition = true;
            while(condition)
            {
                if(counter == response["station"].length)
                    throw("station does not exist")

                if(response["station"][counter]["name"] == stationName)
                {
                    resolve({"stationName": response["station"][counter]["name"] , "key": response["station"][counter]["key"]});  
                    condition = false;
                }
                counter++;
            }
        });
    });
    value = await promise;
    return value;
    
}


//duration = period, intervall = how many entries from latest
getData = async(stationName, typeOfData, duration, intervall) => {
    stationKey = await getStationInfo(stationName, typeOfData);
    stationKey = stationKey["key"];
    let data = [];

    let promise = new Promise(resolve =>
    {
        fetch(`https://opendata-download-metobs.smhi.se/api/version/latest/parameter/${typeOfData}/station/${stationKey}/period/${duration}/data.json`)
        .then(response => response.json())
        .then(response =>  {

            lastIndex = response["value"].length - 1;
            intervallFromLastIndex = response["value"].length - intervall;

            if(intervall == 1)
                resolve(response["value"][lastIndex]);

            else 
            {
                for(i = lastIndex; i >= intervallFromLastIndex; i--)
                {
                    dataItem = response["value"][i];
                    data.push(dataItem);
                }
                resolve(data);
            }
        });
    })

    return await promise;
}

getDataLatestMonths = async(stationName, typeOfData) => {
    stationKey = await getStationInfo(stationName, typeOfData);
    stationKey = stationKey["key"];
    let data = [];
    let promise = new Promise(resolve => 
    {
        fetch(`https://opendata-download-metobs.smhi.se/api/version/latest/parameter/${typeOfData}/station/${stationKey}/period/latest-months/data.json`)
        .then(response => response.json())
        .then(response =>  {
    
            lastIndex = response["value"].length - 1;
            for(i = lastIndex; i >= 0; i--)
            {
                dataItem = response["value"][i];
                data.push(dataItem);
            }
            resolve(data);
        });
    });
 
    return await data;
}

window.addEventListener("load", async()=>{
    object = await getData("Abisko Aut", 1, "latest-months", 2);
    object2 = await getDataLatestMonths("Abisko Aut", 1);
    object3 = await getStationInfo("Abisko Aut", 1);

    console.log(object);
    console.log(object2);
    console.log(object3);
})