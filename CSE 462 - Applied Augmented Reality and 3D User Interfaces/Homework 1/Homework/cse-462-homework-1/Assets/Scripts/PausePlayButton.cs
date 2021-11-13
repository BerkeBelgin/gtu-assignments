using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Video;

public class PausePlayButton : MonoBehaviour
{
    public GameObject obj;
    public VideoPlayer videoPlayer;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Began) {
            Ray ray = Camera.main.ScreenPointToRay(Input.GetTouch(0).position);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit) && hit.collider.gameObject.GetInstanceID() == obj.GetInstanceID()) {
                if (videoPlayer.isPlaying) videoPlayer.Pause();
                else videoPlayer.Play();
            }
        }
    }
}
